#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "fifo_seqnum.h"

int main(int argc, char *argv[])
{
    int serverFd, dummyFd, clientFd;
    char clientFifo[CLINET_FIFO_NAME_LEN];
    struct request req;
    struct response resp;
    int seqNum = 0;

    // umask(0)は権限をまったくマスクしない。
    umask(0);
    /* S_IRUSR: Read by owner.  */
    /* S_IWUSR: Write by owner.  */
    /* S_IWGRP: Execute by group.  */
    if (mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
        errExit("mkfifo %s", SERVER_FIFO);
    
    // サーバー用のFIFOをオープン。
    serverFd = open(SERVER_FIFO, O_RDONLY);
    if (serverFd == -1)
        errExit("open %s", SERVER_FIFO);
    
    // EOFが発生しないように、書き込み用にもオープン
    // 全クライアントがFIFOの書き込み口をクローズした場合にEOFが検知されないようにする
    dummyFd = open(SERVER_FIFO, O_WRONLY);
    if (dummyFd == -1)
        errExit("open %s", SERVER_FIFO);
    
    // サーバがクライアントFIFOへ書き込んだがクライアントがクライアントFIFOを読み取らないとき
    // SIGPIPEが発生するのを避け、write()のエラーとする
    // SIGPIPEはハンドリングしないとプロセスを強制終了させる
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        errExit("signal");
    
    for (;;) {
        // serverFdからsizeof(struct request)分読み取り、req構造体に格納する。
        // その結果がsizeof(struct request)と等しくないとエラーにする
        if (read(serverFd, &req, sizeof(struct request)) != sizeof(struct request)) {
            fprintf(stderr, "Error reading request; discarding\n");
            continue;
        }

        // CLIENT_FIFO_TEMPLATEをpidで成型した文字列をclientFifoに格納
        snprintf(clientFifo, CLINET_FIFO_NAME_LEN, CLINET_FIFO_TEMPLATE, (long) req.pid);

        /* クライアント用のFIFOをオープン */
        clientFd = open(clientFifo, O_WRONLY);
        if (clientFd == -1) {
            printf("open %s\n", clientFifo);
            continue;
        }

        /* レスポンスを返却し、FIFOをclose()する */
        resp.seqNum = seqNum;
        if (write(clientFd, &resp, sizeof(struct response)) != sizeof(struct response))
            fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
        if (close(clientFd) == -1)
            printf("close\n");

        seqNum += req.seqLen;
    }
    
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