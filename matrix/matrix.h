#ifndef MATRIX_H 
#define MATRIX_H  
#include <stdlib.h>
typedef struct vector_t {
        double* data;
        size_t n;
} vector_t;
typedef struct matrix_t {
        double* data;
        size_t n, m;
} matrix_t;
typedef enum error_code_matrix_t {
        NO_MEMORY,
        DIMENSION_ERROR,
} error_code_matrix_t;
double* malloc_array(size_t n);
double* copy_array(double* arr, size_t n);
void error_matrix(error_code_matrix_t error);
vector_t* calloc_vector();
matrix_t* calloc_matrix();
vector_t* create_vector(double* data, size_t n);
matrix_t* create_matrix(double* data, size_t n, size_t m);
vector_t* create_vector_elem(size_t n, double elem);
matrix_t* create_matrix_elem(size_t n, size_t m, double elem);
void set_array(double* arr, size_t n, double elem);
vector_t* copy_vector(vector_t* vector);
matrix_t* copy_matrix(matrix_t* matrix);
void free_vector(vector_t* vector);
void free_matrix(matrix_t* matrix);
vector_t* sum_vector(vector_t* v1, vector_t* v2);
matrix_t* sum_matrix(matrix_t* m1, matrix_t* m2);
double dot_array(double* arr1, double* arr2, size_t n);
double dot_vector(vector_t* v1, vector_t* v2);
matrix_t* dot_matrix(matrix_t* m1, matrix_t* m2);
vector_t* get_matrix_column(matrix_t* matrix, size_t j);
double det_matrix(matrix_t* matrix);
double determinant_recursive(double* arr, int n, int i, int j);
#endif