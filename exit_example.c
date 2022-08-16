#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// atexitは以下のような関数プロトタイプ
// int atexit(void (*function)(void));
// void my_function(void);
// 登録した関数をプロセス終了時に実行する順序は、登録時とは逆になる。

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