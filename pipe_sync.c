#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

char* currTime();

int main(int argc, char *argv[])
{
    int pfd[2];
    int j, dummy;

    if (argc < 2 || strcmp(argv[1], "--help") ==0) 
        errExit("usage error");

    setbuf(stdout, NULL);
    
    printf("%s Parent started\n", currTime());

    if (pipe(pfd) == -1)
        errExit("pipe");
    for (j = 1; j < argc; j++) {
        switch(fork()) {
        case -1:
            errExit(sprintf("fork %d", j));
        case 0:
            if (close(pfd[0]) == -1)
                errExit("close");
            
            // 何か処理を実行して、親プロセスに通知
            sleep(atoi(argv[j]));
            printf("%s Child %d (PID=%ld) closing pipe \n", currTime(), j, (long) getpid());
            if (close(pfd[1] == -1))
                errExit("close");
            _exit(EXIT_SUCCESS);
        default: 
            break;
        }
    }
    if (close(pfd[1]) == -1)
        errExit("close");

    if (read(pfd[0], &dummy, 1) != 0)
        errExit("parent didn't get EOF");
    
    // 何か処理を実行して、子プロセスと同期
    // 結局、子プロセスのパイプが全部closeされたら
    // 親プロセスのブロックが解除されることで同期をとってる。
    // closeの代わりに1バイトだけ送って、状態を取り出して制御したりもできる
    printf("%s Parent ready to go\n", currTime());
    exit(EXIT_SUCCESS);
}

void errExit(char *errmsg) {
    printf("%s\n", errmsg);
    exit(EXIT_FAILURE);
}

char* currTime() {
    static char buf[1000];
    time_t rawtime;
    size_t s;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if (timeinfo == NULL)
        return NULL;
    s = strftime(buf, 1000, "%c", timeinfo);
    return (s == 0) ? NULL : buf;
}