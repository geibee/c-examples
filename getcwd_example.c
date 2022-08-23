#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    FILE *stream;
    char *swd;
    int ret;

    // NULL, 0を与えると、バッファをよしなに割り当てて、コピーしてくれる。
    swd = getcwd(NULL, 0);
    if (!swd) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    ret = chdir("./test");
    if (ret) {
        perror("chdir");
        free(swd);
        exit(EXIT_FAILURE);
    }

    stream = fopen("test.txt", "w");
    if (!stream) {
        perror("fopen");
        free(swd);
        return 1;
    }

    if (fputs("test getcwd\n", stream) == EOF) {
        perror("fputs");
        free(swd);
        return 1;
    }

    if (fclose(stream) == EOF) {
        perror("fclose");
        free(swd);
        return 1;
    }

    ret = chdir(swd);
    if (ret) {
        perror("chidir");
        free(swd);
        exit(EXIT_FAILURE);
    }
    free(swd);
    return 0;
}