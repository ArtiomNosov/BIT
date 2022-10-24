#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define border_val 100
typedef int(*cmp_t)(const void *, const void *);
int cmp(const int* a, const int* b)
{
        return *a - *b;
}
void* get_elem(void* arr, size_t i, size_t size)
{
        return (char*) arr + i * size;
}
void swap(void* a, void* b, void* buf, size_t size)
{
        memcpy(buf, a,   size);                 
        memcpy(a,   b,   size);                 
        memcpy(b,   buf, size);  
}
void bubble_sort(void *base, size_t num, size_t size, cmp_t compare)
{
        char* buf = (char*) malloc(size);   
        void* a = NULL, * b = NULL;

        for(int i = 0; i < num; i++) {
                for(int j = 1; j < num - i; j++) {
                        a = get_elem(base, j - 1, size);
                        b = get_elem(base, j    , size);
                        if (compare(a, b) > 0) {   
                                swap(a, b, buf, size);               
                        }
                }
        }

        free(buf); 
}
int optimum_sort(void *base, size_t num, size_t size, cmp_t compare)
{
        if (num > border_val) {
                qsort(base, num, size, compare);
                return 0;
        } else {
                bubble_sort(base, num, size, compare);
                return 1;
        }
}
void generate_array(int* array, int n)
{
        for (int i = 0; i < n; i++) {
                array[i] = rand() % INT_MAX;
        }
}
void print_array(int* arr, int n, const char* str, const char* sep)
{
        printf("%s", str);
        for (int i = 0; i < n; i++)
        {
                printf("%d%s", arr[i], sep);
        }
}
int main()
{
        int n = 20, m = 1000;
        int size = sizeof(int);
        int* arr_short = (int*) malloc(size * n);
        int* arr_long = (int*) malloc(size * m);
        const char arr_short_name[] = "arr_short\n";
        const char arr_long_name[] = "arr_long\n";
        const char sep[] = "  ";
        generate_array(arr_short, n);
        generate_array(arr_long, m);
        print_array(arr_short, n, arr_short_name, sep);
        printf("\n");
        print_array(arr_long, m, arr_long_name, sep);
        int res_short = optimum_sort(arr_short, n, size, (cmp_t)cmp);
        int res_long = optimum_sort(arr_long, m, size, (cmp_t)cmp);
        const char msg_res[] = "For sorting %s we use sort number %d\n";
        printf(msg_res, arr_short_name, res_short);
        printf(msg_res, arr_long_name, res_long);
        printf("Sorting arrays:\n");
        print_array(arr_short, n, arr_short_name, sep);
        printf("\n");
        print_array(arr_long, m, arr_long_name, sep);
        free(arr_short);
        free(arr_long);
        return 0;
}
