#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

/*
    echo test > test.txt
    ln -s test.txt softlink
    ln test.txt hardlink
    ./stat_example test.txt // すべて5bytes
    ./stat_example softlink // lstat()のみ8bytes
    ./stat_example hardlink // すべて5bytes
*/
int main(int argc, char *argv[])
{
    struct stat sb;
    int ret, fd;

    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    ret = stat(argv[1], &sb);
    if (ret) {
        perror("stat");
        return 1;
    }

    printf("%s is %ld bytes in stat()\n", argv[1], sb.st_size);

    if ((fd = open(argv[1], O_WRONLY)) == -1) {
        perror("open");
        return 1;
    }
        
    ret = fstat(fd, &sb);
    if (ret) {
        perror("stat");
        return 1;
    }

    printf("%s is %ld bytes in fstat()\n", argv[1], sb.st_size);

    ret = lstat(argv[1], &sb);
    if (ret) {
        perror("lstat");
        return 1;
    }

    // lstat()はシンボリックリンク自体の情報を返す
    printf("%s is %ld bytes in lstat()\n", argv[1], sb.st_size);


    return 0;
}