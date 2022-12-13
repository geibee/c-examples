#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pfd[2];

    if (pipe(pfd) == -1) {
        errExit("pipe");
    }

    switch (fork()) {
    case -1:
        errExit("fork");
    case  0:
        printf("This is child ls process and closing reading side...\n");
        if (close(pfd[0]) == -1)
            errExit("close 1");
        
        // 標準出力のfdがclose済みでないことを確認
        if (pfd[1] != STDOUT_FILENO) {
            // dup2は、第二引数のfdをcloseして、第一引数のfdとしてopenする
            // ここでは、標準出力をpfd[1]にリダイレクトしている
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
                errExit("dup2 1");
            // 複製済でもう使わないpfd[1]はclose
            if (close(pfd[1]) == -1)
                errExit("close 2");
        }

        execlp("ls", "ls", (char *) NULL);
        errExit("execlp ls");
        
    default:
        printf("This is parent ls process: break;\n");
        break;
    }

    switch (fork()) {
    case -1:
        errExit("fork");
    case 0:
        printf("This is child wc process and closing reading side...\n");
        if (close(pfd[1]) == -1)
            errExit("close3");

        // 標準入力のfdがclose済でないことを確認
        if (pfd[0] != STDIN_FILENO) {
            // dup2は、第二引数のfdをcloseして、第一引数のfdとしてopenする
            // ここでは、標準入力をpfd[0]にリダイレクトしている
            if (dup2(pfd[0], STDIN_FILENO) == -1)
                errExit("dup2 2");
            // 複製済でもう使わないpfd[0]はclose
            if (close(pfd[0]) == -1)
                errExit("close 4");
        }

        execlp("wc", "wc", "-l", (char *) NULL);
        errExit("execlp wc");
    default:
        printf("This is parent wc process: break;\n");
        break;
    }

    // 親プロセスではパイプを使用しないためすべてクローズ
    if (close(pfd[0]) == -1)
        errExit("close 5");
    if (close(pfd[1]) == -1)
        errExit("close 6");
    // pidを指定しないwait()は、任意の子プロセス1つの終了を待つ
    if (wait(NULL) == -1)
        errExit("wait 1");
    // 2回実行することで、lsとwcの2プロセスの終了を待つ
    if (wait(NULL) == -1)
        errExit("wait 2");
    exit(EXIT_SUCCESS);
}

void errExit(char *errmsg) {
    printf("%s\n", errmsg);
    exit(EXIT_FAILURE);
}
