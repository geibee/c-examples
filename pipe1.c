#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Send parent to child through pipe");
    int filedes[2];

    if (pipe(filedes) == -1)
        printf("pipe() failed");
        exit(1);
    
    switch(fork()) {
    case -1:
        printf("fork() failed");
        exit(1);
    case 0:
        printf("This is child process");
        printf("Closing write side pipe with child...");
        if (close(filedes[1]) == -1)
            printf("close() failed");
            exit(1);
        break;
    default:
        printf("This is parent process");
        printf("Closing read side pipe with parent...");
         if (close(filedes[0]) == -1)
            printf("close() failed");
            exit(1);
        break;
    }
}