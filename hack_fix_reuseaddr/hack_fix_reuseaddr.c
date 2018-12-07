/* (c) komar@evologics.de 2018 */

#include <sys/types.h>
#include <sys/socket.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <err.h>

int (*o_socket)(int domain, int type, int protocol) = NULL;

int socket(int domain, int type, int protocol)
{
    int fd, enable = 1;

    if(!o_socket)
        if ((o_socket = dlsym(RTLD_NEXT, "socket")) == NULL)
            err(1, "dlsym(\"socket\") failed");

    if ((fd = o_socket(domain, type, protocol)) < 0)
        err(1, "o_socket() failed");

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
        err(1, "setsockopt(SO_REUSEADDR) failed");

    return fd;
}
