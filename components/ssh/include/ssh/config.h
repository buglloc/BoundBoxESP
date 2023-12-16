#pragma once

#define SSH_SERVER_PORT      22
#define SSH_SERVER_BACKLOG   5
#define SSH_SERVER_BANNER    "BoundBoxESP\n"

/* WOLFSSL_NONBLOCK is a value assigned to threadCtx->nonBlock
 * and should be a value 1 or 0
 */
#define WOLFSSL_NONBLOCK 1

/* TODO will be ever need WOLFSSL_NUCLEUS here? probably not  */
#define WFD_SET_TYPE fd_set
#define WFD_SET FD_SET
#define WFD_ZERO FD_ZERO
#define WFD_ISSET FD_ISSET

/* TODO check / optimize these values */
#ifndef SSH_HIGHWATER_MARK
    #define SSH_HIGHWATER_MARK 0x3FFF8000 /* 1GB - 32kB */
#endif
