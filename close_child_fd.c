#include <stdio.h>
#include <fcntl.h>

int main() {
    int fd1, fd2, flags1, flags2;
    
    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_WRONLY);

    switch(fork()) {        
    case -1:
        printf("Failed to fork()\n");
        return -1;
    case 0:        
        printf("This is parent\n");
        flags1 = fcntl(fd1, F_GETFL);
        if (flags1 == -1)
            printf("fcntl - F_GETFL\n");
            return -1;

        printf("flags1 is %d\n", flags1);
        if (!close(flags1))
            printf("Failed to close(flags1)\n");
            return -1;

        flags2 = fcntl(fd2, F_GETFL);
        if (flags2 == -1)
            printf("fcntl - F_GETFL\n");
            return -1;

        printf("flags2 is %d\n", flags2);

        if (!close(flags2))
            printf("Failed to close(flags2)\n");
            return -1;

    default:    
        printf("This is child\n");
        flags1 = fcntl(fd1, F_GETFL);
        printf("flags1 is %d\n", flags1);
        if (!close(flags1))
            printf("Failed to close(flags1)\n");
            return -1;

        flags2 = fcntl(fd2, F_GETFL);
        printf("flags2 is %d\n", flags2);

        if (!close(flags2))
            printf("Failed to close(flags2)\n");
            return -1;

    }

    return 0;
}