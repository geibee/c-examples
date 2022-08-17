#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

// 子プロセスでviを起動して、その終了を待つ
// 正常終了した場合は0が返される
// kill -9などでプロセスをkillするとシグナルが返される

int main() {
    int status, ret;
    pid_t pid;

    pid = fork();
    if(pid > 0) {
        printf("I am the parent of pid=%d!\n", pid);
        pid = waitpid(pid, &status, WCONTINUED);
        if(pid == -1) {
            perror("waitpid");            
        } else {
            printf("pid=%d\n", pid);

            if(WIFEXITED(status)) {
                printf("Normal termination with exit status=%d\n",
                       WEXITSTATUS(status)
                );
            } 
            
            if(WIFSIGNALED(status)) {
                printf("Killed by signal=%d%s\n",
                       WTERMSIG(status),
                       WCOREDUMP(status) ? " (dumped core)": ""
                );                
            }
        }        
    } else if(!pid) {
        printf("I am the baby!");
        ret = execl("/bin/vi", "vi", NULL);
    }
}