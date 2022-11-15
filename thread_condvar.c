#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// 条件変数。ここでは、データベースへの書き込みを想定する。
static char ***db;
static int counter = 0;

struct arg_struct {
    int index;
    char *argv;
};

static void *
producer(void *arg)
{
    struct arg_struct *args = arg;
    
    int s = pthread_mutex_lock(&mtx);
    if (s != 0) {
        printf("pthread_mutex_lock failed :%d", s);
        exit(1);
    }
    
    time_t t = time(NULL);            
    db[args->index][0] = args->argv;
    db[args->index][1] = ctime(&t);

    counter++;

    s = pthread_mutex_unlock(&mtx);
    if (s != 0) {
        printf("pthread_mutex_unlock failed :%d", s);
        exit(1);
    }

    s = pthread_cond_signal(&cond);
    if (s != 0) {
        printf("pthread_cond_signal failed :%d", s);
        exit(1);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    for (int j = 1; j < argc; j++) {
        if (j > 4) {
            break;
        }

        printf("argv %d is %s\n", j, argv[j]);
        struct arg_struct arg;
        arg.index = j;
        arg.argv = argv[j];

        pthread_t tid;
        int s = pthread_create(&tid, NULL, producer, (void *)&arg);
        if (s != 0) {
            printf("pthread_create failed :%d", s);
            exit(1);
        }
    }
    
    int db_index = 0;
    bool done = false;

    for (;;) {
        int s = pthread_mutex_lock(&mtx);
        if (s != 0) {
            printf("pthread_mutex_lock failed :%d", s);
            exit(1);
        }

        while (counter > 0) {
            // threadを実行した回数分インクリメント
            printf("record No.%d, is %s, timestamp is %s\n", db_index, db[db_index][0], db[db_index][1]);
            counter--;                        
            db_index++;                        
            done = counter == 0;
        }
        s = pthread_mutex_unlock(&mtx);
        if (s != 0) {
            printf("pthread_mutex_unlock failed :%d", s);
            exit(1);
        }
        if (done)
            break;
    }
    exit(EXIT_SUCCESS);
}