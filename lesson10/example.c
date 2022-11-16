#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define N 10
typedef struct main_struct {
    // uint32_t a;
    // uint16_t b;
    // uint8_t c1;
    // uint8_t c2;
    // uint8_t c3;
} main_struct;


typedef struct main_struct_2 {
    int c1;
} main_struct_2;

int comp_main_struct_2(main_struct_2* a, main_struct_2* b)
{
    int a_1 = a->c1;
    int a_2 = b->c1;
    return a_1 - a_2;
}
void print_arr(main_struct_2* arr, int n)
{
    for (size_t i = 0; i < n; i++)
    {
            printf("%d\n", arr[i].c1);
    }
    
}
int main() {
    main_struct_2 object;
    main_struct_2* arr = malloc(sizeof(main_struct_2) * N);
    for (size_t i = 0; i < N; i++)
    {
        arr[i].c1 = rand() % 100;
    }
    
    print_arr(arr, N);
    qsort(arr, N, sizeof(main_struct_2), comp_main_struct_2);
    printf("sort arr:\n");
    print_arr(arr, N);
    free(arr);
}
