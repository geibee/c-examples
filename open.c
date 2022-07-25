#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main() {

    int fd;
    fd = open("test", O_RDONLY);
    if (fd == -1) {
        printf("failed to open file");
    } else {
        printf("succeeded in opening. fd: %d", fd);
    } 
}