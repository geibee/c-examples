#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef struct {
    int nr_oars;
    char* boat_name;
} dinghy;

/*
  メモリの内容はmemcmp()で比較できる。ただし、構造体は内部にパディングを含む。
  パディングは未初期化の不定値のため、構造体同士の比較はメンバを一つずつ比較する。
*/
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
    int ab, ac, ad, test_test2, test_test3, test_test32;
    dinghy a = { 1, "test"};
    dinghy b = { 1, "testing"};
    dinghy c = { 2, "test"};
    dinghy d = { 1, "test"};
    char* test = "test";
    char* test2 = "test";
    char* test3 = "testing";

    ab = compare_dinghies(&a, &b);
    if (!ab)
        printf("A and B are the same.\n");
    ac = compare_dinghies(&a, &c);
    if (!ac)
        printf("A and C are the same.\n");
    ad = compare_dinghies(&a, &d);
    if (!ad)
        printf("A and D are the same.\n");

    test_test2 = memcmp(test, test2, sizeof(test));
    if (test_test2)
        printf("test and test2 are different.\n");    
    else 
        printf("test and test2 are the same.\n");
        
    test_test3 = memcmp(test, test3, sizeof(test));
    if (test_test3)
        printf("test and test3 are different.\n");    
    else 
        printf("test and test3 are the same.\n");
}