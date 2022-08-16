#include <stdio.h>
#include <unistd.h>

int main() {
    int ret;

    ret = execl("/bin/vi", "vi", "test.txt", NULL);
    if(ret == -1) {
        perror("execl");
    }
}