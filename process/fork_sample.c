#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();
    if(pid == -1) {
        perror("fork");        
    }
    if(!pid) {
        printf("I am the baby!\n");
        const char *args[] = {"print_pid", NULL};
        int ret;

        ret = execv("/usr/local/bin/print_pid", args);
        if(ret == -1) {
            perror("execv");
            exit(EXIT_FAILURE);
        }
    } else if(pid > 0) {
        printf("I am the parent of pid=%d\n", pid);
        const char *args[] = {"print_pid", NULL};
        int ret;

        ret = execv("/usr/local/bin/print_pid", args);
 
    }
}