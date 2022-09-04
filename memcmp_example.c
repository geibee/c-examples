#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef struct {
    int nr_oars;
    char* boat_name;
} dinghy;

int compare_dinghies(dinghy *a, dinghy *b) {
    int ret;

    if (a->nr_oars < b->nr_oars) {
        printf("nr_oars of B is more than A's one.\n");
        return -1;
    }

    if (a->nr_oars > b->nr_oars) {
        printf("nr_oars of A is more than B's one.\n");
        return 1;
    }

    ret = strcmp(a->boat_name, b->boat_name);
    if (ret) 
        printf("boat_name is different from each other.\n");
        return ret;
    
    return 0;
}
int main() {
    int ab, ac, ad;
    dinghy a = { 1, "test"};
    dinghy b = { 1, "testing"};
    dinghy c = { 2, "test"};
    dinghy d = { 1, "test"};

    ab = compare_dinghies(&a, &b);
    if (!ab)
        printf("A and B are the same.\n");
    ac = compare_dinghies(&a, &c);
    if (!ac)
        printf("A and C are the same.\n");
    ad = compare_dinghies(&a, &d);
    if (!ad)
        printf("A and D are the same.\n");
}