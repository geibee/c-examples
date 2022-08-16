#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void out1(void) {
    printf("out1 succeeded!\n");
}
void out2(void) {
    printf("out2 succeeded!\n");
}

void out3(void) {
    printf("out3 succeeded!\n");
}

int main() {
    long atexit_max;
    
    atexit_max = sysconf(_SC_ATEXIT_MAX);
    printf("atext_max=%ld\n", atexit_max);

    if(atexit(out3)) {
        fprintf(stderr, "out2 failed!\n");
    }

    if(atexit(out2)) {
        fprintf(stderr, "out2 failed!\n");
    }

    if(atexit(out1)) {
        fprintf(stderr, "out1 failed!\n");
    }


    return 0;
}