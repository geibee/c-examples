#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void *
threadFunc(void *arg)
{
    char *s = (char *) arg;

    printf("%s", s);

    return (void *) strlen(s);
}

int 
main(int argc, char *argv[])
{
    pthread_t thr;
    pthread_attr_t attr;
    int s;

    s = pthread_attr_init(&attr);
    if (s != 0) {
        printf("pthread_attr_init failed :%d", s);
        exit(1);
    }

    // 初めからデタッチしてあるようにスレッド属性を設定する
    s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (s != 0) {
        printf("pthread_attr_setdetachstate failed :%d", s);
        exit(1);
    }

    // joinを待たず、Hello Worldを標準出力に表示する
    s = pthread_create(&thr, &attr, threadFunc, "Hello World\n");
    if (s != 0) {
        printf("pthread_create failed :%d", s);
        exit(1);
    }

    // スレッドの終了を待たないので、sleepしないと先にmain関数が終わってHello Worldが表示されない
    sleep(atoi(argv[1]));
    
    // 不要になった属性を削除する
    s = pthread_attr_destroy(&attr);
    if (s != 0) {
        printf("pthread_attr_destroy failed :%d", s);
        exit(1);
    }

}