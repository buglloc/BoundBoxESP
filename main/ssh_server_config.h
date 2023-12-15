#pragma once

/* SSH is usually on port 22, but for our example it lives at port 22222 */
#define SSH_PORT 22222

#define SSH_SERVER_BANNER "BoundBoxESP\n"

/* WOLFSSL_NONBLOCK is a value assigned to threadCtx->nonBlock
 * and should be a value 1 or 0
 */
#define WOLFSSL_NONBLOCK 1

/* TODO will be ever need WOLFSSL_NUCLEUS here? probably not  */
#ifdef WOLFSSL_NUCLEUS
    #define WFD_SET_TYPE FD_SET
    #define WFD_SET NU_FD_Set
    #define WFD_ZERO NU_FD_Init
    #define WFD_ISSET NU_FD_Check
#else
    #define WFD_SET_TYPE fd_set
    #define WFD_SET FD_SET
    #define WFD_ZERO FD_ZERO
    #define WFD_ISSET FD_ISSET
#endif

/* TODO check / optimize these values */
#ifndef EXAMPLE_HIGHWATER_MARK
    #define EXAMPLE_HIGHWATER_MARK 0x3FFF8000 /* 1GB - 32kB */
#endif
#ifndef EXAMPLE_BUFFER_SZ
    #define EXAMPLE_BUFFER_SZ 4096
#endif
#define SCRATCH_BUFFER_SZ 1200

void ssh_server_config_init();
