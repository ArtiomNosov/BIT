#include <stdlib.h>
#include <locale.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#ifndef MatrixDoubleH
#define MatrixDoubleH

#define ERROR_FILE_OPEN -3
 
typedef struct MatrixDouble {
    double** Rows;

    size_t RowCount;
    size_t ColumnCount;
} MatrixDouble;

double AssertOpenFile(FILE* file);

MatrixDouble* CreateMatrixDouble(size_t n, size_t m);
void AssertMatrixDouble(MatrixDouble* matrix);
void FreeMatrixDouble(MatrixDouble* matrix);

void MatrixDoublePrdoublef(MatrixDouble* matrix);
MatrixDouble* MatrixDoubleScanf(size_t n, size_t m);

void MatrixDoubleFwrite(MatrixDouble* matrix, const char* fileName);
MatrixDouble* MatrixDoubleFread(const char* fileName);

MatrixDouble* MatrixDoubleRand(size_t n, size_t m);

MatrixDouble* InsertRowMatrixDouble(MatrixDouble* matrix, double* row, size_t m, size_t i);
MatrixDouble* InsertColumnMatrixDouble(MatrixDouble* matrix, double* column, size_t n, size_t j);

MatrixDouble* EraseRowMatrixDouble(MatrixDouble* matrix, size_t i);
MatrixDouble* EraseColumnMatrixDouble(MatrixDouble* matrix, size_t j);

double Determinant(MatrixDouble* matrix);
#endif