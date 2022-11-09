#include "MatrixDouble.h"

typedef struct MatrixDouble MatrixDouble;

double AssertOpenFile(FILE* file)
{
    if (file == NULL) 
    {
        printf("Ошибка открытия файла. Попробуйте другое имя файла.\n");
        scanf("%*c");
        return ERROR_FILE_OPEN;
    }
}

MatrixDouble* CreateMatrixDouble(size_t n, size_t m) // not test
{
    MatrixDouble* res = (MatrixDouble*) malloc(sizeof(MatrixDouble));
    res->Rows = (double**) malloc(sizeof(double*) * n);
    for (size_t i = 0; i < n; i++)
    {
        (res->Rows)[i] = (double*) malloc(sizeof(double) * m);
    }
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            ( (res->Rows)[i] )[j] = (double) 0;
        }
        
    }
    res->RowCount = n;
    res->ColumnCount = m;
    
    return res;
}
void AssertMatrixDouble(MatrixDouble* matrix)
{
    assert(matrix);
    assert(matrix->Rows);
    
}
void FreeMatrixDouble(MatrixDouble* matrix) // not test
{
    for (size_t i = 0; i < matrix->RowCount; i++)
    {
        free((matrix->Rows)[i]);
    }
    free(matrix->Rows);

}

void MatrixDoubleprintf(MatrixDouble* matrix)
{
    AssertMatrixDouble(matrix);

    for (size_t i = 0; i < matrix->RowCount; i++)
    {
        for (size_t j = 0; j < matrix->ColumnCount; j++)
        {
            printf("%d \\ ", *((matrix->Rows)[i] + j));
        }
        printf("\n");
    }
    
}
MatrixDouble* MatrixDoubleScanf(size_t n, size_t m)
{
    MatrixDouble* res = CreateMatrixDouble(n, m);
    AssertMatrixDouble(res);

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            scanf("%d", (res->Rows)[i] + j);
        }
    }
    
    return res;
}

void MatrixDoubleFwrite(MatrixDouble* matrix, const char* fileName)
{
    AssertMatrixDouble(matrix);

    FILE *output = NULL;
    output = fopen(fileName, "wb");
    if(AssertOpenFile(output) == ERROR_FILE_OPEN)
    {
        return;
    }
 
    fwrite(&(matrix->RowCount), sizeof(size_t), 1, output);
    fwrite(&(matrix->ColumnCount), sizeof(size_t), 1, output);
    for (size_t i = 0; i < matrix->RowCount; i++)
    {
        fwrite((matrix->Rows)[i], sizeof(double), matrix->ColumnCount, output);
    }
 
    fclose(output);

}
MatrixDouble* MatrixDoubleFread(const char* fileName)
{
    size_t n = 0, m = 0;
    MatrixDouble* res = NULL;
    FILE *input = NULL;

    input = fopen(fileName, "rb");
    if(AssertOpenFile(input) == ERROR_FILE_OPEN)
    {
        return NULL;
    }
 
    fread(&n, sizeof(size_t), 1, input);
    fread(&m, sizeof(size_t), 1, input);
    res = CreateMatrixDouble(n, m);

    AssertMatrixDouble(res);

    for (size_t i = 0; i < n; i++)
    {
        fread((res->Rows)[i], sizeof(double), m, input);
    }
 
    fclose(input);

    return res;
}

MatrixDouble* MatrixDoubleRand(size_t n, size_t m)
{
    MatrixDouble* res = CreateMatrixDouble(n, m);
    AssertMatrixDouble(res);

    srand(time(NULL));

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            *( (res->Rows)[i] + j ) = rand() - RAND_MAX / 2;
        }
    }

    return res;
}

MatrixDouble* InsertRowMatrixDouble(MatrixDouble* matrix, double* row, size_t m, size_t i)
{
    AssertMatrixDouble(matrix);

    assert(row);
    assert(matrix->ColumnCount == m);
    assert(i <= matrix->RowCount + 1);

    MatrixDouble* res = CreateMatrixDouble(matrix->RowCount + 1, m);
    AssertMatrixDouble(res);

    for (size_t j = 0, k = 0; j < matrix->RowCount; j++, k++)
    {
        if (j == i)
        {
            memcpy((res->Rows)[k], row, sizeof(double) * m);
            k++;
        }
        memcpy((res->Rows)[k], (matrix->Rows)[j], sizeof(double) * m);
    }
    
    return res;
}
MatrixDouble* InsertColumnMatrixDouble(MatrixDouble* matrix, double* column, size_t n, size_t j)
{
    AssertMatrixDouble(matrix);

    assert(column);
    assert(matrix->RowCount == n);
    assert(j <= matrix->ColumnCount + 1);

    MatrixDouble* res = CreateMatrixDouble(n, matrix->ColumnCount + 1);
    AssertMatrixDouble(res);

    for (size_t i = 0; i < res->RowCount; i++)
    {
        memcpy((res->Rows)[i], (matrix->Rows)[i], sizeof(double) * j);
        memcpy((res->Rows)[i] + j, column + i, sizeof(double));
        memcpy((res->Rows)[i] + j + 1, (matrix->Rows)[i] + j, sizeof(double) * (matrix->ColumnCount - j) );
    }
    
    return res;
}

MatrixDouble* EraseRowMatrixDouble(MatrixDouble* matrix, size_t i)
{
    AssertMatrixDouble(matrix);
    assert(i < matrix->RowCount);

    MatrixDouble* res = CreateMatrixDouble(matrix->RowCount - 1, matrix->ColumnCount);
    AssertMatrixDouble(res);

    for (size_t j = 0, k = 0; j < res->RowCount; j++, k++)
    {
        if (j == i)
        {
            k++;
        }
        memcpy((res->Rows)[j], (matrix->Rows)[k], sizeof(double) * matrix->ColumnCount);
    }
    
    return res;
}
MatrixDouble* EraseColumnMatrixDouble(MatrixDouble* matrix, size_t j)
{
    AssertMatrixDouble(matrix);
    assert(j < matrix->ColumnCount);

    MatrixDouble* res = CreateMatrixDouble(matrix->RowCount, matrix->ColumnCount - 1);
    AssertMatrixDouble(res);

    for (size_t i = 0; i < res->RowCount; i++)
    {
        memcpy((res->Rows)[i], (matrix->Rows)[i], sizeof(double) * j);
        memcpy((res->Rows)[i] + j, (matrix->Rows)[i] + j + 1, sizeof(double) * (matrix->ColumnCount - j - 1) );
    }
    
    return res;
}

double Determinant(MatrixDouble* matrix) {

    AssertMatrixDouble(matrix);

    size_t i, j, k, n, m = matrix->RowCount;\
    double d = 0.0;
    MatrixDouble* p = NULL;
    j = 0; d = 0;
    k = 1; //(-1) в степени i
    n = m - 1;
    if (m == 1)
        return matrix->Rows[0][0];
    if (m == 2)
        return matrix->Rows[0][0] * matrix->Rows[1][1] - (matrix->Rows[1][0] * matrix->Rows[0][1]);
    if (m > 2)
        for (i = 0; i < m; i++) {
            p = MatrixDoubleWithoutRowColumn(matrix, i, 0);
            d += k * matrix->Rows[i][0] * Determinant(p);
            FreeMatrixDouble(p);
            k = -k;
        }
    return d;
}
