#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 10

int main(int argc, char *argv[]) {
    int pfd[2];
    char buf[BUF_SIZE];
    int numRead;

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        printf("argc is %d\n", argc);
        printf("argv[1] is %s\n", argv[1]);
        printf("usage error");
        exit(1);
    }

    if (pipe(pfd) == -1) 
        errExit("pipe() failed");
    
    switch (fork()) {
    case -1:
        errExit("fork() failed");
    case 0:
        printf("This is child process\n");
        printf("Closing write side pipe with child...\n");
        if (close(pfd[1]) == -1) {
            printf("close() failed");
            exit(1);
        }
        for (;;) {
            numRead = read(pfd[0], buf, BUF_SIZE);
            if (numRead == -1)
                errExit("read()"); { 
            }
            if (numRead == 0)
                break;
            if (write(1, buf, numRead) != numRead)
                errExit("child failed to write to stdout\n");
        }
        write(1, "\n", 1);
        if (close(pfd[0]) == -1) 
            errExit("close()");
        _exit(EXIT_SUCCESS);
    default:
        printf("This is parent process\n");
        if (close(pfd[0]) == -1) 
            errExit("error close - parent");
        if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1])) 
            errExit("error parent - partial/failed write");
        if (close(pfd[1]) == -1) 
            errExit("error close");
        wait(NULL);
        exit(EXIT_SUCCESS);
    }
}

void errExit(char *errmsg[]) {
    printf("%s\n", errmsg);
    exit(1);
}