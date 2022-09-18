#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void parent(int fd);
void child(int fd);

int main() 
{
    int sockets[2];
    int parent_sock, child_sock;
    pid_t pid;

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) == -1) 
    {
        perror("socketpair");
        exit(1);
    }

    parent_sock = sockets[0];
    child_sock = sockets[1];

    if ((pid = fork()) == 0)
    {
        printf("sockets[0] is %d\n", sockets[0]);
        printf("sockets[1] is %d\n", sockets[1]);
        printf("parent is %d\n", parent_sock);
        printf("child is %d\n", child_sock);
        close(sockets[1]);
        child(sockets[0]);
    } else if (pid > 0)
    {
        printf("sockets[0] is %d\n", sockets[0]);
        printf("sockets[1] is %d\n", sockets[1]);
        printf("parent is %d\n", parent_sock);
        printf("child is %d\n", child_sock);
        close(sockets[0]);
        parent(sockets[1]);
    } else 
    {
        perror("fork");
        exit(1);
    }
}

void parent(int fd) 
{
    printf("this is parent\n ");
    char *msg, c, sent_msg;
    msg = "hello, world\n";
    

    while (c = *msg++)
    {
        if (write(fd, &c, 1) != 1) {
            perror("write");
        }

        if (read(fd, &sent_msg, 1)) {
            perror("read");
        }
        putchar(sent_msg);
    }

    // printf("sent_msg is %s\n", *sent_msg);
    close(fd);
}

void child(int fd) {
    printf("this is child\n");
    char c;
    while (read(fd, &c, 1) == 1)
    {
        c = toupper(c);
        if (write(fd, &c, 1) != 1) {
            perror("read");
        }
    }
    close(fd);
}