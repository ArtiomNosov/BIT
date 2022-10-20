#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef int(*cmp_t)(const void *, const void *);
int* generate_array(int* array, int n)
{
        for (int i = 0; i < n; i++) {
                array[i] = rand() % INT_MAX;
        }

        return array;
}
int comp (const int *, const int *);
void print_array(int* arr, int n, const char* sep)
{
        for (int i = 0; i < n; i++) {
                printf("%d%s", arr[i], sep);
        }
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
void bubble_sort_int(int *base, size_t num, size_t size, cmp_t compare)
{
        int buf = 0;

        for(int i = 0; i < num; i++) {
                for(int j = 1; j < num - i; j++) {
                        if (compare(base + j - 1, base + j) > 0) {   
                                buf = base[j - 1];
                                base[j - 1] = base[j];  
                                base[j] = base[j - 1];
                                // swap(base + j - 1, base + j, &buf, size); 
                        }
                }
        }
}
int main()
{
        size_t end = 20000, steps_count = 5;
        clock_t start, stop;
        int step = end / steps_count, num = 0, size = sizeof(int), seconds = 0;
        int* array = (int*) malloc(sizeof(int) * end), * gen_array = NULL;
        char str_stat[] = "Sorting %d elements with %s\n";

        srand(0);

        for (int i_step = 1; i_step < steps_count + 1; i_step++) {
                printf(str_stat, step * i_step, "buble sort");

                gen_array = generate_array(array, step * i_step);

                start = clock();
                num = i_step * step;
                bubble_sort(gen_array, num, size, (cmp_t)comp);
                stop = clock();
                print_array(gen_array, 10, "   ");

                seconds = (stop - start) / CLK_TCK;

                printf("\tbenchmark: %d seconds\n", seconds);
        }

        free(array);

        return 0;
}
int comp (const int *i, const int *j)
{
    return *i - *j;
}