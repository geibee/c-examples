#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    pthread_t t1;
    void *res;

    int s;

    s = pthread_create(&t1, NULL, threadFunc, "Hello world\n");
    if (s != 0) {
        printf("pthread_create failed :%d", s);
        exit(1);
    }

    printf("Message from main()\n");
    s = pthread_join(t1, &res);
    if (s != 0) {
        printf("pthread_join failed :%d", s);
        exit(1);
    }

    printf("Thread returned %ld\n", (long) res);
    exit(EXIT_SUCCESS);
}