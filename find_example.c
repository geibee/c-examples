#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int find_file_in_dir(const char *path, const char *file)
{
    struct dirent *entry;
    int ret = 1;
    DIR *dir;

    dir = opendir(path);

    errno = 0;
    while ((entry = readdir(dir)) != NULL) {
        // strcmp returns 0 when two arguments are the same.
        // if(0) won't run codes in block, but if(1) runs.
        if (!strcmp(entry->d_name, file)) {
            ret = 0;
            printf("%s found!\n", file);
            break;
        }
    }

    // readdir() returns NULL if it failed.
    if (errno && !entry) 
        perror("readdir");
    

    closedir(dir);
    return ret;
}

int main() 
{
    int ret;
    
    printf("Start\n");
    ret = find_file_in_dir("test", "test.txt");
    if (ret) {
        perror("find_file_in_dir");
        return 1;
    }
    return 0;
}