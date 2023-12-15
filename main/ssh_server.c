/* ssh_server.c
 *
 * Copyright (C) 2014-2022 wolfSSL Inc.
 *
 * This file is part of wolfSSH.
 *
 * wolfSSH is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * wolfSSH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with wolfSSH.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ssh_server_config.h"
#include "ssh_server.h"
#include "tx_rx_buffer.h"


#include <esp_task_wdt.h>
#include <wolfssl/wolfcrypt/logging.h>


/* note our actual buffer is used by RTOS threads, and eventually interrupts */
static volatile byte sshStreamTransmitBufferArray[ExternalTransmitBufferMaxLength];
static volatile byte sshStreamReceiveBufferArray[ExternalReceiveBufferMaxLength];

static const char * TAG = "ssh_server";

static const char samplePasswordBuffer[] =
    "jill:upthehill\n"
    "jack:fetchapail\n";


static const char samplePublicKeyEccBuffer[] =
    "ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIMoBFbg9zagjN1z2vBi5eE62qG/9vCxsZXlAiNcmTFak";


static const char samplePublicKeyRsaBuffer[] =
    "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQDD5skB0CnUQOBUMFdiwQRzf0Zg/B9gKsAsB+3IuPPP+OS5qeq1YkFjq3BtQiV+AwhKUIk/72+H4usTul2Z2BQ+BQeuzua9/Ht7VhdlqJYgC4h2mJ/hPeWnSPjzzjvY5Ar9G+EuGEtYyMaQ3fZ+0XqnvrXs4ENEpQ5angPfD77XDX1xzTw3JjjdIFqnFH/F/P3VJuypx9eTwVLqCH0yFQsUC+qFy1pQJYB8DUrMHtVPsl27Zd2EwZnCyC1ADEQiV1xTb+kiBK6jejydWpZqjHEDVaU8TDkkfk11NzhJx8+3hvcsA4/y5L+VECkUhQB3JhloOuQd0QKSrEMrcdEzp+o7 buglloc\n";


/* Map user names to passwords */
/* Use arrays for username and p. The password or public key can
 * be hashed and the hash stored here. Then I won't need the type. */
typedef struct PwMap {
    byte type;
    byte username[32];
    word32 usernameSz;
    byte p[WC_SHA256_DIGEST_SIZE];
    struct PwMap* next;
} PwMap;


typedef struct PwMapList {
    PwMap* head;
} PwMapList;

enum {
    WS_SELECT_FAIL,
    WS_SELECT_TIMEOUT,
    WS_SELECT_RECV_READY,
    WS_SELECT_ERROR_READY
};

typedef struct {
    WOLFSSH* ssh;
    int fd;
    word32 id;
    char nonBlock;
} thread_ctx_t;


/* find a byte character [str] of length [bufSz] within [buf];
 * returns byte position if found, otherwise zero
 * TODO what if bufSz > 255?
 */
static byte find_char(const byte* str, const byte* buf, word32 bufSz)
{
    const byte* cur;
    while (bufSz) {
        cur = str;
        while (*cur != '\0') {
            if (*cur == *buf)
                return *cur;
            cur++;
        }
        buf++;
        bufSz--;
    }

    return 0;
}


static int dump_stats(thread_ctx_t* ctx)
{
    ESP_LOGE(TAG,"dumpstats");
    char stats[1024];
    word32 statsSz;
    word32 txCount, rxCount, seq, peerSeq;

    wolfSSH_GetStats(ctx->ssh, &txCount, &rxCount, &seq, &peerSeq);

    WSNPRINTF(stats,
        sizeof(stats),
        "Statistics for Thread #%u:\r\n"
        "  txCount = %u\r\n  rxCount = %u\r\n"
        "  seq = %u\r\n  peerSeq = %u\r\n",
        ctx->id,
        txCount,
        rxCount,
        seq,
        peerSeq);
    statsSz = (word32)strlen(stats);

    fprintf(stderr, "%s", stats);
    return wolfSSH_stream_send(ctx->ssh, (byte*)stats, statsSz);
}

static WC_INLINE int wSelect(int nfds,
                             WFD_SET_TYPE* recvfds,
                             WFD_SET_TYPE *writefds,
                             WFD_SET_TYPE *errfds,
                             struct timeval* timeout)
{
    return select(nfds, recvfds, writefds, errfds, timeout);
}

/*
 * tcp_select; call wSelect & check for success or fail
 */
static WC_INLINE int tcp_select(SOCKET_T socketfd, int to_sec)
{
    WFD_SET_TYPE recvfds, errfds;
    int nfds = (int)socketfd + 1;
    struct timeval timeout = { (to_sec > 0) ? to_sec : 0, 0 };
    int result;

    WFD_ZERO(&recvfds);
    WFD_SET(socketfd, &recvfds);
    WFD_ZERO(&errfds);
    WFD_SET(socketfd, &errfds);

    result = wSelect(nfds, &recvfds, NULL, &errfds, &timeout);

    if (result == 0)
        return WS_SELECT_TIMEOUT;
    else if (result > 0) {
        if (WFD_ISSET(socketfd, &recvfds))
            return WS_SELECT_RECV_READY;
        else if (WFD_ISSET(socketfd, &errfds))
            return WS_SELECT_ERROR_READY;
    }

    return WS_SELECT_FAIL;
}

static int NonBlockSSH_accept(WOLFSSH* ssh)
{
    int ret;
    int error;
    int sockfd;
    int select_ret = 0;
    int max_wait = 100;
    ESP_LOGI(TAG,"Start NonBlockSSH_accept");

    ret = wolfSSH_accept(ssh);
    error = wolfSSH_get_error(ssh);
    sockfd = (int)wolfSSH_get_fd(ssh);

    while (ret != WS_SUCCESS &&
            (error == WS_WANT_READ || error == WS_WANT_WRITE)) {

        max_wait--;
        if (max_wait < 0) {
            error = WS_FATAL_ERROR;
        }
/*
        if (error == WS_WANT_READ)
            ESP_LOGE(TAG,"... client would read block\n");
        else if (error == WS_WANT_WRITE)
            ESP_LOGE(TAG,"... client would write block\n");
*/

        select_ret = tcp_select(sockfd, 1);
        if (select_ret == WS_SELECT_RECV_READY  ||
            select_ret == WS_SELECT_ERROR_READY ||
            error == WS_WANT_WRITE) {
            ret = wolfSSH_accept(ssh);
            error = wolfSSH_get_error(ssh);
        }
        else if (select_ret == WS_SELECT_TIMEOUT)
            error = WS_WANT_READ;
        else
            error = WS_FATAL_ERROR;

#ifdef DEBUG_WDT
        /* RTOS yield */
        vTaskDelay(100 / portTICK_PERIOD_MS);
        /* if we get panic faults, perhaps the watchdog needs attention? */
        esp_task_wdt_reset();
#endif
    }
    ESP_LOGI(TAG,"Exit NonBlockSSH_accept");

    return ret;
}

/* #define SSH_SERVER_PROFILE */

#ifdef SSH_SERVER_PROFILE
    static int MaxSeenRxSize = 0;
    static int MaxSeenTxSize = 0;
#endif


/*
 * server_worker is the main thread for a given SSH connection
 **/
static THREAD_RETURN WOLFSSH_THREAD server_worker(void* vArgs)
{
    int ret;

    /* we'll create a local instance of threadCtx since it will be
     * handed off to potentially multiple separate threads
     */
    thread_ctx_t* threadCtx = (thread_ctx_t*)vArgs;

    if (!threadCtx->nonBlock)
        ret = wolfSSH_accept(threadCtx->ssh);
    else
        ret = NonBlockSSH_accept(threadCtx->ssh);

    if (ret == WS_SUCCESS) {
        byte* this_rx_buf = NULL;

        int backlogSz = 0, rxSz, txSz, stop = 0, txSum;

        init_tx_rx_buffer(TXD_PIN, RXD_PIN);

        /*
         * we'll stay in this loop then entire time this worker thread has
         * a valid SSH connection open
         */
        do {
            /* int show_msg = 0; TODO optionally disable echo of text to USB port */
            int has_err = 0;
            this_rx_buf = (byte*)&sshStreamReceiveBufferArray;

            if (!stop) {
                do {
                    int error = 0;
                    socklen_t len = sizeof(error);
                    int retval = getsockopt(threadCtx->fd,
                                           SOL_SOCKET, SO_ERROR, &error, &len);

                    if (retval != 0) {
                        /* if we can't even call getsockopt, give up */
                        stop = 1;
                        ESP_LOGE(TAG,"ERROR: getsockopt unable to query socket fd!");
                    }
                    if (error != 0) {
                        /* socket has a non zero error status */
                        ESP_LOGE(TAG,"ERROR: getsockopt returned error socket fd!");
                        stop = 1;
                    }

                    /* this is a blocking call, awaiting an SSH keypress
                     * unless nonBlock = 1 (normally we are NOT blocking) */
                    rxSz = wolfSSH_stream_read(threadCtx->ssh,
                                               this_rx_buf + backlogSz,
                                               EXAMPLE_BUFFER_SZ);

                    if (rxSz <= 0) {
                        rxSz = wolfSSH_get_error(threadCtx->ssh);
                        if (rxSz == WS_WANT_READ || rxSz == WS_WANT_WRITE)
                        {
                            /* WS_WANT_READ or WS_WANT_WRITE but no data yet */
                            rxSz = 0;
                        }
                        else
                        {
                            /*  any other negative value is an error */
                            has_err = 1;
                            ESP_LOGE(TAG,"wolfSSH_stream_read error!");
                        }
                    }

                    taskYIELD();
                } while ((WOLFSSL_NONBLOCK == 0) /* we'll wait only when not using non-blocking socket */
                         &&
                         (rxSz == WS_WANT_READ || rxSz == WS_WANT_WRITE));

                /*
                 * if there's data in the external transmit buffer, typically from UART,
                 * we'll send that to the SSH client.
                 */
                if (ExternalTransmitBufferSz() > 0) {
                    ESP_LOGI(TAG,"Tx UART!");

                    /* our actual transit buffer array is not on the local stack
                     * to minimize RTOS requirements; we'll setup a pointer to it.
                     *
                     * Note this is a *different* buffer from the external (UART)
                     * which may change during RTOS threads, and future interrupt code.
                     * */
                    byte* sshStreamTransmitBuffer = (byte*)&sshStreamTransmitBufferArray;

                    /* We'll get a copy of the buffer and
                     * set _ExternalTransmitBufferSz to zero
                     *
                     * Note this is thread safe, getting both data and size.
                     */
                    int thisSize = Get_ExternalTransmitBuffer(&sshStreamTransmitBuffer);

                    if (sshStreamTransmitBuffer == NULL) {
                        /* TODO this is an error as the buffer should never
                         * be null if the size was larger than zero */
                        stop = 1;
                    }
                    else {
                        /* note thisSize will not have changed from any other
                         *  thread, since we have a copy and fixed size */
                        wolfSSH_stream_send(threadCtx->ssh,
                                            sshStreamTransmitBuffer,
                                            thisSize);
                    }


                }

                /*
                 * if we received any data from the SSH client, we'll store it in the
                 * External REceived Buffer for later sending to the UART
                 *
                 * Reminder negative values for WS_WANT_READ || WS_WANT_WRITE
                 */
                if (rxSz > 0) {
                    /* append external data, for something such as UART forwarding
                     * note any prior data saved in the buffer was _ExternalReceiveBufferSz
                     *
                     * Here we perform the thread-safe equivalent of:
                     *
                        memcpy((byte*)&_ExternalReceiveBuffer[_ExternalReceiveBufferSz],
                               buf,
                               rxSz);
                        _ExternalReceiveBufferSz = rxSz;
                     */
                    Set_ExternalReceiveBuffer(this_rx_buf, rxSz);

                    backlogSz += rxSz;
                    txSum = 0;
                    txSz = 0;


                    while (backlogSz != txSum && txSz >= 0 && !stop) {
                        /* we typically do NOT want to re-echo TTY data
                         * but it can be configured to do so by setting
                         * SSH_SERVER_ECHO to a value of 1
                         **/
                        if (SSH_SERVER_ECHO == 1) {
                            /* reminder we moved data from external buffer
                             * to our local buf, and this is ECHO
                             */
                            txSz = wolfSSH_stream_send(threadCtx->ssh,
                                                       this_rx_buf + txSum,
                                                       backlogSz - txSum);
                        }
                        else {
                            txSz = backlogSz - txSum;
                        }

                        if (txSz > 0) {
                            byte c;
                            const byte matches[] = { 0x03, 0x05, 0x06, 0x00 };

                            c = find_char(matches, this_rx_buf + txSum, txSz);

                            switch (c) {

                            case 0x03:
                                stop = 1;
                                break;

                            case 0x06:
                                if (wolfSSH_TriggerKeyExchange(threadCtx->ssh)
                                        != WS_SUCCESS) {
                                    stop = 1;
                                }
                                break;

                            case 0x05:
                                if (dump_stats(threadCtx) <= 0) {
                                    stop = 1;
                                }
                                break;
                            }

                            txSum += txSz;
                        }
                        else if (txSz != WS_REKEYING) {
                            stop = 1;
                        }

                        taskYIELD();
#ifdef DEBUG_WDT
        /* if we get panic faults, perhaps the watchdog needs attention? */
        esp_task_wdt_reset();
#endif
                    } /* while */

                    if (txSum < backlogSz) {
                        memmove(this_rx_buf, this_rx_buf + txSum, backlogSz - txSum);
                    }
                    backlogSz -= txSum;
                }
                else {
                    /* we might have negative values for non-blocking Rx
                     * during WS_WANT_READ || WS_WANT_WRITE */
                    if (has_err == 1)
                    {
                        stop = 1;
                    }
                }
            }

#ifdef DEBUG_WDT
            /* if we get panic faults, perhaps the watchdog needs attention? */
            taskYIELD();
            vTaskDelay(pdMS_TO_TICKS(10));
            esp_task_wdt_reset();
#endif
        } while (!stop);
    } /* if (ret == WS_SUCCESS) */
    }

    wolfSSH_stream_exit(threadCtx->ssh, 0);

    /* check if open before closing */
    if (threadCtx->fd != SOCKET_INVALID) {
        ESP_LOGI(TAG,"Close sockfd socket");
        close(threadCtx->fd);
    }

    wolfSSH_free(threadCtx->ssh);
    free(threadCtx);

    return 0;
}

#ifndef NO_FILESYSTEM
static int load_file(const char* fileName, byte* buf, word32 bufSz)
{
    FILE* file;
    word32 fileSz;
    word32 readSz;

    if (fileName == NULL) return 0;

    if (WFOPEN(&file, fileName, "rb") != 0)
        return 0;
    fseek(file, 0, SEEK_END);
    fileSz = (word32)ftell(file);
    rewind(file);

    if (fileSz > bufSz) {
        fclose(file);
        return 0;
    }

    readSz = (word32)fread(buf, 1, fileSz, file);
    if (readSz < fileSz) {
        fclose(file);
        return 0;
    }

    fclose(file);

    return fileSz;
}
#endif /* !NO_FILESYSTEM */



/* returns buffer size on success */
static int load_key(byte isEcc, byte* buf, word32 bufSz)
{
    word32 sz = 0;

#ifndef NO_FILESYSTEM
    const char* bufName;
    bufName = isEcc ? "./keys/server-key-ecc.der" :
                       "./keys/server-key-rsa.der";
    sz = load_file(bufName, buf, bufSz);
#else
    /* using buffers instead */
    if (isEcc) {
        if ((word32)sizeof_ecc_key_der_256 > bufSz) {
            return 0;
        }
        WMEMCPY(buf, ecc_key_der_256, sizeof_ecc_key_der_256);
        sz = sizeof_ecc_key_der_256;
    }
    else {
        if ((word32)sizeof_rsa_key_der_2048 > bufSz) {
            return 0;
        }
        WMEMCPY(buf, rsa_key_der_2048, sizeof_rsa_key_der_2048);
        sz = sizeof_rsa_key_der_2048;
    }
#endif

    return sz;
}


/* our own little c word32 to array */
static WC_INLINE void c32toa(word32 u32, byte* c)
{
    c[0] = (u32 >> 24) & 0xff;
    c[1] = (u32 >> 16) & 0xff;
    c[2] = (u32 >>  8) & 0xff;
    c[3] =  u32 & 0xff;
}

static PwMap* PwMapNew(PwMapList* list,
                       byte type,
                       const byte* username,
                       word32 usernameSz,
                       const byte* p,
                       word32 pSz) {
    PwMap* map;

    map = (PwMap*)malloc(sizeof(PwMap));
    if (map != NULL) {
        wc_Sha256 sha;
        byte flatSz[4];

        map->type = type;
        if (usernameSz >= sizeof(map->username))
            usernameSz = sizeof(map->username) - 1;
        memcpy(map->username, username, usernameSz + 1);
        map->username[usernameSz] = 0;
        map->usernameSz = usernameSz;

        wc_InitSha256(&sha);
        c32toa(pSz, flatSz);
        wc_Sha256Update(&sha, flatSz, sizeof(flatSz));
        wc_Sha256Update(&sha, p, pSz);
        wc_Sha256Final(&sha, map->p);

        map->next = list->head;
        list->head = map;
    }

    return map;
}


static void PwMapListDelete(PwMapList* list)
{
    if (list != NULL) {
        PwMap* head = list->head;

        while (head != NULL) {
            PwMap* cur = head;
            head = head->next;
            memset(cur, 0, sizeof(PwMap));
            free(cur);
        }
    }
}



static int LoadPasswordBuffer(byte* buf, word32 bufSz, PwMapList* list)
{
    char* str = (char*)buf;
    char* delimiter;
    char* username;
    char* password;

    /* Each line of passwd.txt is in the format
     *     username:password\n
     * This function modifies the passed-in buffer. */

    if (list == NULL)
        return -1;

    if (buf == NULL || bufSz == 0)
        return 0;

    while (*str != 0) {
        delimiter = strchr(str, ':');
        if (delimiter == NULL) {
            return -1;
        }
        username = str;
        *delimiter = 0;
        password = delimiter + 1;
        str = strchr(password, '\n');
        if (str == NULL) {
            return -1;
        }
        *str = 0;
        str++;
        if (PwMapNew(list,
                     WOLFSSH_USERAUTH_PASSWORD,
                     (byte*)username,
                     (word32)strlen(username),
                     (byte*)password,
                     (word32)strlen(password)) == NULL) {

            return -1;
        }
    }

    return 0;
}


static int LoadPublicKeyBuffer(byte* buf, word32 bufSz, PwMapList* list)
{
    char* str = (char*)buf;
    char* delimiter;
    byte* publicKey64;
    word32 publicKey64Sz;
    byte* username;
    word32 usernameSz;
    byte  publicKey[300];
    word32 publicKeySz;

    /* Each line of passwd.txt is in the format
     *     ssh-rsa AAAB3BASE64ENCODEDPUBLICKEYBLOB username\n
     * This function modifies the passed-in buffer. */
    if (list == NULL)
        return -1;

    if (buf == NULL || bufSz == 0)
        return 0;

    while (*str != 0) {
        /* Skip the public key type. This example will always be ssh-rsa. */
        delimiter = strchr(str, ' ');
        if (delimiter == NULL) {
            return -1;
        }
        str = delimiter + 1;
        delimiter = strchr(str, ' ');
        if (delimiter == NULL) {
            return -1;
        }
        publicKey64 = (byte*)str;
        *delimiter = 0;
        publicKey64Sz = (word32)(delimiter - str);
        str = delimiter + 1;
        delimiter = strchr(str, '\n');
        if (delimiter == NULL) {
            return -1;
        }
        username = (byte*)str;
        *delimiter = 0;
        usernameSz = (word32)(delimiter - str);
        str = delimiter + 1;
        publicKeySz = sizeof(publicKey);

        if (Base64_Decode(publicKey64,
            publicKey64Sz,
            publicKey,
            &publicKeySz) != 0) {

            return -1;
        }

        if (PwMapNew(list,
            WOLFSSH_USERAUTH_PUBLICKEY,
            username,
            usernameSz,
            publicKey,
            publicKeySz) == NULL) {

            return -1;
        }
    }

    return 0;
}


static int wsUserAuth(byte authType,
                      WS_UserAuthData* authData,
                      void* ctx)
{
    PwMapList* list;
    PwMap* map;
    byte authHash[WC_SHA256_DIGEST_SIZE];

    if (ctx == NULL) {
        ESP_LOGE(TAG,"wsUserAuth: ctx not set");
        return WOLFSSH_USERAUTH_FAILURE;
    }

    if (authType != WOLFSSH_USERAUTH_PASSWORD &&
        authType != WOLFSSH_USERAUTH_PUBLICKEY) {

        return WOLFSSH_USERAUTH_FAILURE;
    }

    /* Hash the password or public key with its length. */
    {
        wc_Sha256 sha;
        byte flatSz[4];
        wc_InitSha256(&sha);
        if (authType == WOLFSSH_USERAUTH_PASSWORD) {
            c32toa(authData->sf.password.passwordSz, flatSz);
            wc_Sha256Update(&sha, flatSz, sizeof(flatSz));
            wc_Sha256Update(&sha,
                authData->sf.password.password,
                authData->sf.password.passwordSz);
        }
        else if (authType == WOLFSSH_USERAUTH_PUBLICKEY) {
            c32toa(authData->sf.publicKey.publicKeySz, flatSz);
            wc_Sha256Update(&sha, flatSz, sizeof(flatSz));
            wc_Sha256Update(&sha,
                authData->sf.publicKey.publicKey,
                authData->sf.publicKey.publicKeySz);
        }
        wc_Sha256Final(&sha, authHash);
    }

    list = (PwMapList*)ctx;
    map = list->head;

    while (map != NULL) {
        if (authData->usernameSz == map->usernameSz &&
            memcmp(authData->username, map->username, map->usernameSz) == 0) {

            if (authData->type == map->type) {
                if (memcmp(map->p, authHash, WC_SHA256_DIGEST_SIZE) == 0) {
                    return WOLFSSH_USERAUTH_SUCCESS;
                }
                else {
                    return (authType == WOLFSSH_USERAUTH_PASSWORD ?
                            WOLFSSH_USERAUTH_INVALID_PASSWORD :
                            WOLFSSH_USERAUTH_INVALID_PUBLICKEY);
                }
            }
            else {
                return WOLFSSH_USERAUTH_INVALID_AUTHTYPE;
            }
        }
        map = map->next;
    }

    return WOLFSSH_USERAUTH_INVALID_USER;
}


#ifdef WOLFSSH_TEST_THREADING

typedef THREAD_RETURN WOLFSSH_THREAD THREAD_FUNC(void*);


static WC_INLINE void ThreadStart(THREAD_FUNC fun, void* args, THREAD_TYPE* thread) {
#ifdef SINGLE_THREADED
    (void)fun;
    (void)args;
    (void)thread;
#elif defined(_POSIX_THREADS) && !defined(__MINGW32__)
#ifdef WOLFSSL_VXWORKS
    {
        pthread_attr_t myattr;
        pthread_attr_init(&myattr);
        pthread_attr_setstacksize(&myattr, 0x10000);
        pthread_create(thread, &myattr, fun, args);
    }
#else
    pthread_create(thread, 0, fun, args);
#endif
    return;
#elif defined(WOLFSSL_TIRTOS)
    /* Initialize the defaults and set the parameters. */
    Task_Params taskParams;
    Task_Params_init(&taskParams);
    taskParams.arg0 = (UArg)args;
    taskParams.stackSize = 65535;
    *thread = Task_create((Task_FuncPtr)fun, &taskParams, NULL);
    if (*thread == NULL) {
        printf("Failed to create new Task\n");
    }
    Task_yield();
#else
    * thread = (THREAD_TYPE)_beginthreadex(0, 0, fun, args, 0, 0);
#endif
}


static WC_INLINE void ThreadJoin(THREAD_TYPE thread)
{
#ifdef SINGLE_THREADED
    (void)thread;
#elif defined(_POSIX_THREADS) && !defined(__MINGW32__)
    pthread_join(thread, 0);
#elif defined(WOLFSSL_TIRTOS)
    while (1) {
        if (Task_getMode(thread) == Task_Mode_TERMINATED) {
            Task_sleep(5);
            break;
        }
        Task_yield();
    }
#else
    int res = WaitForSingleObject((HANDLE)thread, INFINITE);
    assert(res == WAIT_OBJECT_0);
    res = CloseHandle((HANDLE)thread);
    assert(res);
    (void)res; /* Suppress un-used variable warning */
#endif
}


static WC_INLINE void ThreadDetach(THREAD_TYPE thread) {
#ifdef SINGLE_THREADED
    (void)thread;
#elif defined(_POSIX_THREADS) && !defined(__MINGW32__)
    pthread_detach(thread);
#elif defined(WOLFSSL_TIRTOS)
#if 0
    while (1) {
        if (Task_getMode(thread) == Task_Mode_TERMINATED) {
            Task_sleep(5);
            break;
        }
        Task_yield();
    }
#endif
#else
    int res = CloseHandle((HANDLE)thread);
    assert(res);
    (void)res; /* Suppress un-used variable warning */
#endif
}

#endif /* WOLFSSH_TEST_THREADING */


/*
 * this my_IORecv callback is WIP and not currently used

TODO decide if we want to use callbacks or not

static int my_IORecv(WOLFSSH* ssh, void* buff, word32 sz, void* ctx) {
    int ret;

    ID  cepid;
    if (ctx != NULL)cepid = *(ID *)ctx;
    else return WS_CBIO_ERR_GENERAL;

    ret = tcp_rcv_dat(cepid, buff, sz, TMO_FEVR);
    byte* buf = NULL;
    int backlogSz = 0;

    ret = wolfSSH_stream_read(threadCtx->ssh,
        buf + backlogSz,
        EXAMPLE_BUFFER_SZ);
    ret = WOLFSSL_SUCCESS;
    return ret;
}

 * this my_IORecv callback is WIP and not currently used

static int my_IOSend(WOLFSSH* ssh, void* buff, word32 sz, void* ctx) {
    int ret;
    ID  cepid;

    if (ctx != NULL)cepid = *(ID *)ctx;
    else return WS_CBIO_ERR_GENERAL;

    ret = tcp_snd_dat(cepid, buff, sz, TMO_FEVR);
    ret = WOLFSSL_SUCCESS;

    return ret;
}
*/

static WC_INLINE void tcp_set_nonblocking(SOCKET_T* sockfd)
{
    #ifdef USE_WINDOWS_API
        unsigned long blocking = 1;
        int ret = ioctlsocket(*sockfd, FIONBIO, &blocking);
        if (ret == SOCKET_ERROR)
            err_sys_with_errno("ioctlsocket failed");
    #elif defined(WOLFSSL_MDK_ARM) || defined(WOLFSSL_KEIL_TCP_NET) \
        || defined (WOLFSSL_TIRTOS)|| defined(WOLFSSL_VXWORKS) \
        || defined(WOLFSSL_ZEPHYR)
         /* non blocking not supported, for now */
    #else
        int flags = fcntl(*sockfd, F_GETFL, 0);
        if (flags < 0)
        ESP_LOGE(TAG,"fcntl get failed");
            flags = fcntl(*sockfd, F_SETFL, flags | O_NONBLOCK);
        if (flags < 0)
            ESP_LOGE(TAG,"fcntl set failed");
    #endif
}

void server_test(void *arg)
{
    int DEFAULT_PORT = SSH_UART_PORT;
    int ret = WOLFSSL_SUCCESS; /* assume success until proven wrong */
    int sockfd = 0; /* the socket that will carry our secure connection */
    struct sockaddr_in servAddr;
    int                on;

    static int mConnd = SOCKET_INVALID;

    /* declare wolfSSL objects */
    WOLFSSH_CTX *ctx = NULL; /* the wolfSSL context object*/

    PwMapList pwMapList;

    word32 defaultHighwater = EXAMPLE_HIGHWATER_MARK;
    word32 threadCount = 0;
    char multipleConnections = 1;
    char useEcc = 0;

#ifdef HAVE_SIGNAL
    signal(SIGINT, sig_handler);
#endif

#ifdef DEBUG_WOLFSSL
    wolfSSL_Debugging_ON();
    ESP_LOGI(TAG,"Debug ON v0.2c");
    /* TODO ShowCiphers(); */
#endif /* DEBUG_WOLFSSL */

#ifdef DEBUG_WOLFSSH
    wolfSSH_Debugging_ON();
    /* TODO ShowCiphers(); */
#endif /* DEBUG_WOLFSSL */


#ifndef WOLFSSL_TLS13
    ret = WOLFSSL_FAILURE;
   ESP_LOGE(TAG,"\r\nERROR: Example requires TLS v1.3.\n");
#endif /* WOLFSSL_TLS13 */

    /* Initialize the server address struct with zeros */
    memset(&servAddr, 0, sizeof(servAddr));

    /* Fill in the server address */
    servAddr.sin_family      = AF_INET; /* using IPv4      */
    servAddr.sin_port        = htons(DEFAULT_PORT); /* on DEFAULT_PORT */
    servAddr.sin_addr.s_addr = INADDR_ANY; /* from anywhere   */
    ESP_LOGI(TAG, "init: %d", DEFAULT_PORT);


    if (ret == WOLFSSL_SUCCESS) {
        /* Upon successful completion, socket() shall return
         * a non-negative integer, the socket file descriptor.
        */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd > 0) {
            ESP_LOGI(TAG,"socket creation successful");
        }
        else {
            /* TODO show errno */
            ret = WOLFSSL_FAILURE;
           ESP_LOGE(TAG,"\r\nERROR: failed to create a socket.\n");
        }
    }
    else {
        ESP_LOGE(TAG,"Skipping socket create.\n");
    }


    if (ret == WOLFSSL_SUCCESS) {
        /* make sure server is setup for reuse addr/port */
        int soc_ret;

        on = 1;
        soc_ret = setsockopt(sockfd,
                             SOL_SOCKET,
                             SO_REUSEADDR,
                             (char*)&on,
                             (socklen_t)sizeof(on)
                            );

        if (soc_ret == 0) {
            ESP_LOGI(TAG,"setsockopt re-use addr successful");
        }
        else {
            /* TODO show errno */
            ret = WOLFSSL_FAILURE;
            ESP_LOGE(TAG,"\r\nERROR: failed to setsockopt addr on socket.\n");
        }
    }
    else {
        ESP_LOGE(TAG,"Skipping setsockopt addr\n");
    }

    if (ret == WOLFSSL_SUCCESS) {
        /* Bind the server socket to our port */
        int soc_ret = bind(sockfd,
                           (struct sockaddr*)&servAddr,
                                       sizeof(servAddr)
                          );

        if (soc_ret > -1) {
            ESP_LOGI(TAG,"socket bind successful.");
        }
        else {
            ret = WOLFSSL_FAILURE;
            ESP_LOGE(TAG,"\r\nERROR: failed to bind to socket.\n");
        }
    }

    if (ret == WOLFSSL_SUCCESS) {
        int backlog = 5;
        int soc_ret = listen(sockfd, backlog);
        if (soc_ret > -1) {
            ESP_LOGI(TAG,"socket listen successful\n");
        }
        else {
           ret = WOLFSSL_FAILURE;
           ESP_LOGE(TAG,"\r\nERROR: failed to listen to socket.\n");
        }
    }

    if (wolfSSH_Init() != WS_SUCCESS) {
        ESP_LOGE(TAG,"Couldn't initialize wolfSSH.\n");
        exit(EXIT_FAILURE);
    }

    ctx = wolfSSH_CTX_new(WOLFSSH_ENDPOINT_SERVER, NULL);
    if (ctx == NULL) {
        ESP_LOGE(TAG,"Couldn't allocate SSH CTX data.\n");
        exit(EXIT_FAILURE);
    }


    memset(&pwMapList, 0, sizeof(pwMapList));

    /* authorization is a callback, so assign it here: wsUserAuth */
    wolfSSH_SetUserAuth(ctx, wsUserAuth);

    /* set the login banner message as defined in ssh_server_config.h */
    wolfSSH_CTX_SetBanner(ctx, SSH_SERVER_BANNER);

    {
        const char* bufName;
        byte buf[SCRATCH_BUFFER_SZ];
        word32 bufSz;

        bufSz = load_key(useEcc, buf, SCRATCH_BUFFER_SZ);
        if (bufSz == 0) {
            ESP_LOGE(TAG, "Couldn't load key.\n");
            exit(EXIT_FAILURE);
        }
        if (wolfSSH_CTX_UsePrivateKey_buffer(ctx,
                                             buf,
                                             bufSz,
                                             WOLFSSH_FORMAT_ASN1) < 0) {
            ESP_LOGE(TAG,"Couldn't use key buffer.\n");
            exit(EXIT_FAILURE);
        }

        bufSz = (word32)strlen(samplePasswordBuffer);
        memcpy(buf, samplePasswordBuffer, bufSz);
        buf[bufSz] = 0;
        LoadPasswordBuffer(buf, bufSz, &pwMapList);

        bufName = useEcc ? samplePublicKeyEccBuffer :
                           samplePublicKeyRsaBuffer;
        bufSz = (word32)strlen(bufName);
        memcpy(buf, bufName, bufSz);
        buf[bufSz] = 0;
        LoadPublicKeyBuffer(buf, bufSz, &pwMapList);
    }

    listen(sockfd, 5);

    do {
        int      clientFd = 0;
        struct sockaddr_in clientAddr;
        socklen_t     clientAddrSz = sizeof(clientAddr);
#ifndef SINGLE_THREADED
        THREAD_TYPE   thread;
        ESP_LOGI(TAG,"Found SINGLE_THREADED defined");
#endif
        WOLFSSH*      ssh;

        /* we'll create a new instance of threadCtx since it will be handed off to
         * potentially multiple separate threads
         */
        thread_ctx_t* threadCtx;

        threadCtx = (thread_ctx_t*)malloc(sizeof(thread_ctx_t));
        if (threadCtx == NULL) {
            ESP_LOGE(TAG,"Couldn't allocate thread context data.\n");
            exit(EXIT_FAILURE);
        }
ESP_LOGI(TAG,"accept - 000");
        /*
         * optionally register some callbacks (these are not working)
        wolfSSH_SetIORecv(ctx, my_IORecv);
        wolfSSH_SetIOSend(ctx, my_IOSend);
         */

        ssh = wolfSSH_new(ctx);
        ESP_LOGI(TAG,"accept - 0111");
        if (ssh == NULL) {
            ESP_LOGE(TAG,"Couldn't allocate SSH data.\n");
            exit(EXIT_FAILURE);
        }

        ESP_LOGI(TAG,"accept - 0222");
        wolfSSH_SetUserAuthCtx(ssh, &pwMapList);
        /* Use the session object for its own highwater callback ctx */
        if (defaultHighwater > 0) {
            wolfSSH_SetHighwaterCtx(ssh, (void*)ssh);
            wolfSSH_SetHighwater(ssh, defaultHighwater);
        }
ESP_LOGI(TAG,"accept - 0333");
        clientFd = accept(sockfd,
                          (struct sockaddr*)&clientAddr,
                          &clientAddrSz
                         );
ESP_LOGI(TAG,"accept!!!!");
        if (clientFd == -1) {
            ESP_LOGI(TAG,"ERROR: failed accept");
            exit(EXIT_FAILURE);
        }

        if (WOLFSSL_NONBLOCK)
            tcp_set_nonblocking(&clientFd);

        wolfSSH_set_fd(ssh, (int)clientFd);

        threadCtx->ssh = ssh;
        threadCtx->fd = clientFd;
        threadCtx->id = threadCount++;
        threadCtx->nonBlock = WOLFSSL_NONBLOCK;

        ESP_LOGI(TAG,"server_worker started.");
#ifndef SINGLE_THREADED
        ThreadStart(server_worker, threadCtx, &thread);

        if (multipleConnections)
            ThreadDetach(thread);
        else
            ThreadJoin(thread);
#else
        server_worker(threadCtx);
#endif /* SINGLE_THREADED */
        ESP_LOGI(TAG,"server_worker completed.");

    } while (multipleConnections);
    ESP_LOGI(TAG,"all servers exited.");

    PwMapListDelete(&pwMapList);
    wolfSSH_CTX_free(ctx);
    if (wolfSSH_Cleanup() != WS_SUCCESS) {
        ESP_LOGE(TAG,"Couldn't clean up wolfSSH.\n");
        exit(EXIT_FAILURE);
    }
#if defined(HAVE_ECC) && defined(FP_ECC) && defined(HAVE_THREAD_LS)
    wc_ecc_fp_free(); /* free per thread cache */
#endif

    ESP_LOGI(TAG,"server test done!");

    /* Cleanup and return */

    if (mConnd != SOCKET_INVALID) {
        ESP_LOGI(TAG,"Close mConnd socket");
        close(mConnd); /* Close the connection to the client   */
        mConnd = SOCKET_INVALID;
    }
    if (sockfd != SOCKET_INVALID) {
        ESP_LOGI(TAG,"Close sockfd socket");
        close(sockfd); /* Close the socket listening for clients   */
        sockfd = SOCKET_INVALID;
    }

    return;
}




