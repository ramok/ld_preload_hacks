/* (c) komar@evologics.de 2018 */

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>

#ifndef SHIFT_PORT
#define SHIFT_PORT 60000
#endif

#ifdef DEBUG
#define FPRINTF(...) fprintf(__VA_ARGS__)
#else
#define FPRINTF(...)
#endif

int (*o_bind)(int sockfd, const struct sockaddr *addr, socklen_t addrlen) = NULL;

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    struct sockaddr_in *addr_in = (struct sockaddr_in *)addr;
    in_port_t port = ntohs(addr_in->sin_port);

    if(!o_bind)
        if ((o_bind = dlsym(RTLD_NEXT, "bind")) == NULL)
            err(1, "dlsym(\"bind\") failed");

    if (port > 0 && port < 1024) {
        FPRINTF(stderr, "LD_PRELOAD hack: port %d was moved to %d\n", port, port + SHIFT_PORT);
        addr_in->sin_port = htons(port + SHIFT_PORT);
    }

    return o_bind(sockfd, addr, addrlen);
}
