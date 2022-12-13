#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("My pid=%d\n", getpid());
    printf("Parent's pid=%d\n", getppid());
}