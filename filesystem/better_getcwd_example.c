#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main() 
{
    FILE *stream;
    int swd_fd, ret;
    
    swd_fd = open(".", O_RDONLY);
    if (swd_fd == -1) {
        perror("open");
    }

    ret = chdir("test");
    if (ret) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    stream = fopen("better_getcwd.txt", "w");
    if (!stream) {
        perror("fopen");
        return 1;
    }

    if (fputs("test better_getcwd\n", stream) == EOF) {
        perror("fputs");
        return 1;
    }

    if (fclose(stream) == EOF){
        perror("chdir");
        exit(EXIT_FAILURE);
    }
    
    ret = fchdir(swd_fd);
    if (ret) {
        perror("fchdir");
        exit(EXIT_FAILURE);
    }

    ret = close(swd_fd);
    if (ret) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}