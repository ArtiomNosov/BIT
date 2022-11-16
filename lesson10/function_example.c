#include <stdio.h>
#include <stdint.h>

void func() {
    printf("Do Work\n");
}

typedef struct main_struct {
    int a;
    void (*func) ();
} main_struct;


int main() {
    main_struct object;
    object.func = func;
    object.func();
    printf("%ld", sizeof(object));
}
