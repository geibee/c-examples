#include "fifo_seqnum.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

static char clientFifo[CLINET_FIFO_NAME_LEN];

static void removeFifo(void)
{
    // unlink()はファイルを削除する
    unlink(clientFifo);
}

int main(int argc, char *argv[]) 
{
    int serverFd, clientFd;
    struct request req;
    struct response resp;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        errExit(argv[0]);
    
    umask(0);
    
    // CLIENT_FIFO_TEMPLATEにgetpid()の戻り値を当てはめた文字列をclientFifoに格納
    snprintf(clientFifo, CLINET_FIFO_NAME_LEN, CLINET_FIFO_TEMPLATE, (long) getpid());
    if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
        errExit(sprintf("mkfifo %s", clientFifo));
    
    if (atexit(removeFifo) != 0)
        errExit("atexit");

    req.pid = getpid();
    req.seqLen = (argc > 1) ? ((atoi(argv[1]) > 0) ? atoi(argv[1]) : 1) : 1;

    serverFd = open(SERVER_FIFO, O_WRONLY);
    if (serverFd == -1)

        errExit(SERVER_FIFO);

    if (write(serverFd, &req, sizeof(struct request)) != sizeof(struct request))
        // fatal
        errExit("Can't write to server");

    clientFd = open(clientFifo, O_RDONLY);
    if (clientFd == -1)
        errExit(clientFifo);
    
    if (read(clientFd, &resp, sizeof(struct response)) != sizeof(struct response))
        // fatal
        errExit("Can't read response from server");
    
printf("%d\n", resp.seqNum);
    exit(EXIT_SUCCESS);
}


void errExit(char *errmsg) {
    printf("%s\n", errmsg);
    exit(EXIT_FAILURE);
}
