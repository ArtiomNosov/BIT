#include "matrix.h"
double* malloc_array(size_t n)
{
        double* res = (double*) malloc(n * sizeof(double));
        if (res == NULL)
                error_matrix(NO_MEMORY);
        return res;
}
double* copy_array(double* arr, size_t n)
{
        double* res = malloc_array(n);
        for (size_t i = 0; i < n; i++)
                res[i] = arr[i];
        return res;
}
void error_matrix(error_code_matrix_t error)
{
        // ERRORS
}
vector_t* calloc_vector()
{
        vector_t* res = (vector_t*) calloc(1, sizeof(vector_t));
        if (res == NULL)
                error_matrix(NO_MEMORY);
        return res;
}
matrix_t* calloc_matrix()
{
        matrix_t* res = (matrix_t*) calloc(1, sizeof(matrix_t));
        if (res == NULL)
                error_matrix(NO_MEMORY);
        return res;
}
vector_t* create_vector(double* data, size_t n)
{
        vector_t* res = calloc_vector();
        res->data = copy_array(data, n);
        res->n = n;
        return res;
}
matrix_t* create_matrix(double* data, size_t n, size_t m)
{
        matrix_t* res = calloc_matrix();
        res->data = copy_array(data, n * m);
        res->n = n;
        res->m = m;
        return res;
}
void set_array(double* arr, size_t n, double elem)
{
        if (arr == NULL)
                return;
        for (size_t i = 0; i < n; i++)
                arr[i] = elem;
}
vector_t* create_vector_elem(size_t n, double elem)
{
        vector_t* res = calloc_vector();
        res->n = n;
        res->data = malloc_array(n);
        set_array(res->data, n, elem);
        return res;
}
matrix_t* create_matrix_elem(size_t n, size_t m, double elem)
{
        matrix_t* res = calloc_matrix();
        res->n = n;
        res->m = m;
        res->data = malloc_array(n * m);
        set_array(res->data, n * m, elem);
        return res;
}
vector_t* copy_vector(vector_t* vector)
{
        if (vector == NULL)
                return NULL;
        size_t n = vector->n;
        return create_vector(vector->data, n);
}
matrix_t* copy_matrix(matrix_t* matrix)
{
        if (matrix == NULL)
                return NULL;
        size_t n = matrix->n, m = matrix->m;
        return create_matrix(matrix->data, n, m);
}
void free_vector(vector_t* vector)
{
        if (vector != NULL)
                free(vector->data);
        free(vector);
}
void free_matrix(matrix_t* matrix)
{
        if (matrix != NULL)
                free(matrix->data);
        free(matrix);
}
vector_t* sum_vector(vector_t* v1, vector_t* v2)
{
        if (v1 == NULL)
                return copy_vector(v2);
        if (v2 == NULL)
                return copy_vector(v1);
        if (v1->n != v2->n)
                error_matrix(DIMENSION_ERROR);
        size_t n = v1->n;
        vector_t* res = create_vector_elem(n, 0.0);
        for (size_t i = 0; i < n; i++)
                res->data[i] = v1->data[i] + v2->data[i];
        return res;
}
matrix_t* sum_matrix(matrix_t* m1, matrix_t* m2)
{
        if (m1 == NULL)
                return copy_matrix(m2);
        if (m2 == NULL)
                return copy_matrix(m1);
        if ((m1->n != m2->n) || (m1->m != m2->m))
                error_matrix(DIMENSION_ERROR);
        size_t n = m1->n;
        size_t m = m1->m;
        matrix_t* res = create_matrix_elem(n, m, 0.0);
        for (size_t i = 0; i < n * m; i++)
                res->data[i] += m1->data[i] + m2->data[i];
        return res;
}
double dot_array(double* arr1, double* arr2, size_t n)
{
        if (arr1 == NULL || arr2 == NULL)
                return 0.0;
        double res = 0.0;
        for (size_t i = 0; i < n; i++)
                res += arr1[i] * arr2[i];
        return res;
}
double dot_vector(vector_t* v1, vector_t* v2)
{
        if (v1 == NULL || v2 == NULL)
                return 0.0;
        if (v1->n != v2->n)
                error_matrix(DIMENSION_ERROR);
        size_t n = v1->n;
        return dot_array(v1->data, v2->data, n);
}
matrix_t* dot_matrix(matrix_t* m1, matrix_t* m2)
{
        if (m1 == NULL || m2 == NULL)
                return NULL;
        if (m1->m != m2->n)
                error_matrix(DIMENSION_ERROR);
        size_t n = m1->n;
        size_t m = m2->m;
        size_t q = m1->m;
        double dot_res = 0.0;
        matrix_t* res = create_matrix_elem(n, m, 0.0);
        vector_t* v1 = NULL;
        for (size_t i = 0; i < n; i++) 
                for (size_t j = 0; j < m; j++) {
                        dot_res = 0.0;
                        for (size_t k = 0; k < q; k++)
                                dot_res += m1->data[i*m + k] * m2->data[k*m + j];
                        res->data[i*m + j] = dot_res;
                }
        return res;
}
vector_t* get_matrix_column(matrix_t* matrix, size_t j)
{
        if (matrix == NULL)
                return NULL;
        size_t m = matrix->m;
        size_t n = matrix->n;
        if (j > matrix->m)
                error_matrix(DIMENSION_ERROR);
        vector_t* res = create_vector_elem(n, 0.0);
        for (size_t i = 0; i < n; i++)
                res->data[i] = matrix->data[i*m + j];
        return res;
}
MatrixDouble* matrix_to_matrix_integer(matrix_t* matrix)
{
        if (matrix == NULL)
                return NULL;
        size_t n = matrix->n, m = matrix->m;
        MatrixDouble* res = CreateMatrixDouble(matrix->n, matrix->m);
        for (size_t i = 0; i < n; i++)
                for (size_t j = 0; j < m; j++)
                        res->Rows[i][j] = matrix->data[i*m + j];
        return res;
}
double det_matrix(matrix_t* matrix)
{
        if (matrix == NULL)
                return 0.0;
        MatrixDouble* m = matrix_to_matrix_integer(matrix);
        double res = Determinant(m);
        FreeMatrixDouble(m);
        return res;
}
