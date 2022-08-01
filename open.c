#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

main() {
    FILE *stream;
    FILE *std_output_stream;
    FILE *stderr_stream;
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
            printf("error in reading test file");
        } else {
            printf("buf=%s\n", buf);
            printf("result=%s\n", result);
            if (fclose(stream) == EOF)
                printf("error in closing test file");
        }
    }
    std_output_stream = fdopen(1, "w");
    if (fputs("standard output test\n", std_output_stream) == EOF) 
        printf("error in writing to standard output");

    if (fclose(std_output_stream) == EOF) 
        printf("error in closing standard output");
    stderr_stream = fdopen(2, "w");
    if (fputs("standard error test\n", stderr_stream) == EOF) 
        printf("error in writing to standard err");

    if (fclose(stderr_stream) == EOF) 
        printf("error in closing standard err");
}