#include <stdlib.h>
#define border_val 100
typedef int(*cmp_t)(const void *, const void *);
int cmp(const int* a, const int* b)
{
        return *a - *b;
}
void bubble_sort(void *base, size_t num, size_t size, cmp_t compare)
{
        // your code here
}
int optimum_sort(void *base, size_t num, size_t size, cmp_t compare)
{
        if (num > border_val) {
                // quick sort 
        } else {
                // bubble sort
        }
}
void generate_array(int* array, int n)
{
        for (int i = 0; i < n; i++) {
                array[i] = rand() % INT_MAX;
        }
}
int main()
{
        // your code here
        return 0;
}
