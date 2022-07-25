#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

main() {
    FILE *stream;
    char buf[5];
    char *result;
    int fd;

    fd = open("test", O_RDONLY);
    if (fd == -1) {
        printf("failed to open file");
    } else {
        printf("succeeded in opening. fd: %d\n", fd);
    }    
    stream = fdopen(fd, "r");    
    if (!stream) {
        printf("failed to open fd");
    } else {
        result = fgets(buf, 5, stream);
        if (result == EOF) {
            printf("error");
        } else {
            printf("buf=%s\n", buf);
            printf("result=%s\n", result);
        }
    }
}