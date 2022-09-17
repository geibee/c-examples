#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"
int main(int argc, char *argv[])
{
    int fd, flags;
    char template[] = "/tmp/testXXXXXX";

    setbuf(stdout, NULL);

    // make a temporary file that has unique name
    fd = mkstemp(template);
    if (fd == -1) 
        printf("mkstemp");
        return -1;
    
    // lseek is change file offset
    // SEEK_CUR changes offset to sum second arg with current offset
    printf("File offset before fork(): %lld\n",        
            (long long) lseek(fd, 0, SEEK_CUR));

    // fctl does an operation of second argument
    // F_GETFL return the file access mode and the file status flags
    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
        printf("fcntl - F_GETFL");
        return -1;
    printf("O_APPEND flag before fork() is: %s \n",
            (flags & O_APPEND) ? "on" : "off");

    switch(fork()) {
    case -1:
        printf("fork");
        return -1;
    
    // child process
    case 0:
        // set file offset at 1000byte
        if (lseek(fd, 1000, SEEK_SET) == -1)
            printf("lseek");
            return -1;
        
        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            printf("fcntl - F_GETFL");
            return -1;
        
        // append O_APPEND to flags
        flags |= O_APPEND;
        if (fcntl(fd, F_SETFL, flags) == -1)
            printf("fcntl - F_SETFL");
            return -1;
        _exit(EXIT_SUCCESS);

    // parent process
    default:
        // wait(NULL) will block the parent process 
        // until any of its children has finished.
        // If the child terminates before the parent process reaches wait(NULL)
        // then the child process turns to a zombie process 
        // until its parent waits on it and its released from memory.
        if (wait(NULL) == -1)
            printf("wait");
            return -1;
        printf("Child has exited\n");

        printf("File offset in parent: %lld\n",
                (long long) lseek(fd, 0, SEEK_CUR));
        
        flags = fcntl(fd, F_GETFL);
        if (flags == -1)
            printf("fcntl - F_GETFL");
            return -1;
        printf("O_APPEND flag in parent is: %s\n",
                (flags & O_APPEND) ? "on" : "off");
        exit(EXIT_SUCCESS);
    }

}