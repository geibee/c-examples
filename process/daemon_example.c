#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#define NR_OPEN 1024

int main(void) {
    pid_t pid;
    int i;

    pid = fork();
    if(pid == -1) {
        return -1;
    } else if(pid != 0) {
        exit(EXIT_SUCCESS);
    }

    if(setsid() == -1) {
        return -1;
    }
    
    if(chdir("/") == -1) {
        return -1;
    }



    for(i = 0; i < NR_OPEN; i++) {
        close(i);
    }

    open("/dev/null", O_RDWR);
    dup(0);
    dup(0);

    execl("/usr/sbin/nginx", "nginx", NULL);
    return 0;
}