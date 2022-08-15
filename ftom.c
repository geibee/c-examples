#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd, len;
    long sysconf_output;
    void *p;

    if((fd = open("test.txt", O_WRONLY)) == -1) {
        perror("open");
        exit(-1);
    }

    sysconf_output = sysconf(_SC_PAGESIZE);
    printf("page size is %ld\n", sysconf_output);

    len = 100;
    p = mmap(0, len, PROT_READ, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    if(munmap(p, len) == -1) {
        perror("mmap");
        return 1;
    }
    return 0;
}