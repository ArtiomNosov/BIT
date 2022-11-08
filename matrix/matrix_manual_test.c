#include <stdio.h>
#include "matrix.h"
typedef const char* str;
void print_matrix(matrix_t* matrix, str name)
{
        printf("\nMatrix: %s\n", name);
        if (matrix == NULL)
                return;
        for (size_t i = 0; i < matrix->n; i++) {
                for (size_t j = 0; j < matrix->m; j++)
                        printf("%.0f\t", matrix->data[i*matrix->m + j]);
                printf("\n");
        }
        
}
int main()
{
        double arr[] = {1, 2, 3, 2, 1, 2, 3, 2, 1};
        size_t n = 3, m = 3;
        matrix_t* m1 = create_matrix(arr, n, m);
        matrix_t* m2 = copy_matrix(m1);
        matrix_t* m3 = dot_matrix(m1, m2);
        print_matrix(m3, "dot");
        matrix_t* m4 = sum_matrix(m1, m2);
        print_matrix(m4, "sum");
        matrix_t* m5 = create_matrix_elem(n, m, 0.0);
        print_matrix(m5, "create_matrix_elem");
        double d = det_matrix(m1);
        printf("\nd: %d\n", d);
        free_matrix(m1);
        free_matrix(m2);
        free_matrix(m3);
        free_matrix(m4);
        free_matrix(m5);
        return 0;
}