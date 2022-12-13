#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char *argv[])
{
    pthread_mutex_t mtx;
    pthread_mutexattr_t mtxAttr;
    int s, type;

    s = pthread_mutexattr_init(&mtxAttr);
    if (s != 0) {
            printf("pthread_mutexattr_init failed :%d", s);
            exit(1);
    }

    // 以下のmutex操作時にエラー検知する。
    // 1. 同じmutexを同じスレッドからネストして2度ロックしようとした場合
    // 2. 所有していないmutex(他スレッドがロックしたmutex)をアンロックしようとした場合
    // 3. ロック中でないmutexをアンロックしようとした場合
    s = pthread_mutexattr_settype(&mtxAttr, PTHREAD_MUTEX_ERRORCHECK);
    if (s != 0) {
            printf("pthread_mutexattr_settype failed :%d", s);
            exit(1);
    }

    s = pthread_mutex_init(&mtx, &mtxAttr);
    if (s != 0) {
            printf("pthread_mutex_init failed :%d", s);
            exit(1);
    }
    
    // スタティックな初期値PTHREAD_MUTEX_INITIALIZERで初期化されていないmutexは破棄する必要がある。
    // アンロック状態 かつ どのスレッドもロックしようとしていないものに限り安全に破棄できる
    s = pthread_mutexattr_destroy(&mtxAttr);
    if (s != 0) {
            printf("pthread_mutexattr_destroy failed :%d", s);
            exit(1);
    }

    s = pthread_mutex_destroy(&mtx);
    if (s != 0) {
            printf("pthread_mutex_destroy failed :%d", s);
            exit(1);
    }

    return 0;
}