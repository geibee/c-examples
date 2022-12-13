#define _XOPEN_SOURCE
#include <stdlib.h>
#include <signal.h>

int main() {
    do {
        int ret;

        ret = system("pidof rudderd");
        if (WIFSIGNALED(ret) &&
            (WTERMSIG(ret) == SIGINT ||
             WTERMSIG(ret) == SIGQUIT))
             {
                break;        
             }
    } while(1);
}