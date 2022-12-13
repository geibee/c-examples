#include <sys/un.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SV_SOCK_PATH "/tmp/us_socket"
#define BUF_SIZE 100

int main(int args, char *argv[]) 
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1) {
        printf("Error create socket");
        exit(1);
    }
    printf("client socket is %d", sfd);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sfd, (struct sockaddr *) &addr,
                sizeof(struct sockaddr_un)) == -1) {
        printf("Cannot connect");
        exit(1);
    }

    while ((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if (write(sfd, buf, numRead) != numRead)
            printf("partial/failed write");
            exit(1);

    if (numRead == -1) {
        printf("read");
        exit(1);
    }
    exit(EXIT_SUCCESS);
}
