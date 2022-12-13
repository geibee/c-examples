#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define SV_SOCK_PATH "/tmp/us_socket"
#define BUF_SIZE 100
#define BACKLOG 5

int main (int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
        printf("Error create socket");
        exit(1);
    }
    printf("listening socket is %d", sfd);

    if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT) {
        printf("remove SV_SOCK_PATH");
        exit(1);
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (bind(sfd, (struct sockpacket *) &addr, sizeof(struct sockaddr_un)) == -1) {
        printf("bind");
        exit(1);
    }

    if (listen(sfd, BACKLOG) == -1) {
        printf("listen");
        exit(1);
    }
    
    for (;;) {
        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1) {
            printf("accept");
            exit(1);
        }

        while ((numRead = read(cfd, buf, BUF_SIZE)) > 0)
            if (write(STDOUT_FILENO, buf, numRead) != numRead)
                printf("partial/failed write");

        if (numRead == -1) {
            printf("read");
            exit(1);
        }

        if (close(cfd) == -1)
            printf("close");
            exit(1);
    }
}

