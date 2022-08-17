int test_ptr(int data) {
    int *ptr;
    
    ptr = &data;
    printf("original data is %d\n", data);
    printf("original ptr is %d\n", *ptr);
    *&data = 1;
    printf("modified data is %d\n", data);
    printf("modified ptr is %d\n", *ptr);

    return data;
}

/*
  int型の変数をとるtest_ptrの引数は値(値渡し)なので、
  main関数内でのtest_ptr(data)として呼び出してもdataの値は変更されない。
  data = test_ptr(data)とかするともちろん値は変更される。
*/
int main() {
    int data = 10;
    test_ptr(data);
    // returned data is 10
    printf("returned data is %d\n", data);
}