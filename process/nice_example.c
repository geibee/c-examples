#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int ret;

    errno = 0;
    ret = nice(atoi(argv[1]));
    if(ret == -1 && errno != 0) {
        perror("nice");
    } else {
        printf("nice value is now %d\n", ret);
    }
    return 0;
}