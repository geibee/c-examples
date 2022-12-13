#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return -1;
    } else if(pid != 0) {
        exit(EXIT_SUCCESS);
    }

    if(setsid() == -1) {
        perror("setsid");
        return -1;
    }
    return 0;
}
