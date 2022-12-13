#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static volatile int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

static void *
threadFunc(void *arg)
{
    int loops = *((int *) arg);
    int loc, j, s;

    for (j = 0; j < loops; j++) {
        s = pthread_mutex_lock(&mtx);
        if (s != 0) {
            printf("pthread_mutex_lock failed :%d", s);
            exit(1);
        }

        loc = glob;
        loc++;
        glob = loc;

        s = pthread_mutex_unlock(&mtx);
        if (s != 0) {
            printf("pthread_mutex_unlock failed :%d", s);
            exit(1);
        }
    }
    return NULL;
}

int 
main(int argc, char *argv[]) 
{
    pthread_t t1, t2;
    int loops, s;

    loops = (argc > 1) ? atoi(argv[1]) : 10000000;
    
    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) {
        printf("t1: pthread_create failed :%d", s);
        exit(1);
    }
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) {
        printf("t2: pthread_create failed :%d", s);
        exit(1);
    }

    s = pthread_join(t1, NULL);
    if (s != 0) {
        printf("t1: pthread_join failed :%d", s);
        exit(1);
    }

    s = pthread_join(t2, NULL);
    if (s != 0) {
        printf("t2: pthread_join failed :%d", s);
        exit(1);
    }

    printf("glob = %d\n", glob);
    exit(EXIT_SUCCESS);

}