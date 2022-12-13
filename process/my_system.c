#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
  strace -o my_system.log ./my_system vi test.txt
  別タブでkill -9 531119
  cat my_system.log
    execve("./my_system", ["./my_system", "vi", "test.txt"], envp[] // 31 vars ) = 0
    (中略)
    write(1, "I am the parent of pid=531119!\n", 31) = 31
    wait4(531119, *status, WCONTINUED, NULL) = -1 EFAULT (Bad address)
        // [EFAULT]
 	    // status 引数か rusage 引数が違法なアドレスを指しています。 (子プロセスの終了前には検出されないことがあります。)
    --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=531119, si_uid=1000, si_status=137, si_utime=0, si_stime=0} ---
    exit_group(0)
    +++ exited with 0 +++
*/

void out(void) {
    printf("child process exited");
}

int my_system(const char *cmd) {
    int ret, status;
    pid_t pid;

    pid = fork();
    if(pid > 0) {
        printf("I am the parent of pid=%d!\n", pid);
        if(waitpid(pid, status, WCONTINUED) == -1) {
            return -1;
        } else if((WIFEXITED(status))) {
            return WEXITSTATUS(status);            
        }
        return -1;
    } else if(!pid) {
        if (atexit(out)) {
            fprintf(stderr, "atexit() failed!\n");
        }

        printf("I am the baby!");
        ret = execl("/bin/sh", "sh", "-c", cmd, NULL);
        if(ret == -1) {
            perror("execl");
        }

        exit(-1);
    
    } else if (pid == -1) {
        printf("fork");
    }
}

int main(int argc, char *argv[]) {
    my_system(argv[1]);
}