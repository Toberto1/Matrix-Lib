#include "myAO.h"
#include "utility.h"

/*
* Description: Allocates space of a matrix
* Parameters:  
*   - int rows: the number of rows for the matrix
*   - int cols: the number of columns for the matrix
* Return: double** matrix: A pointer to the new allocated matrix
*/
double** allocateMatrix(int rows, int cols) {

    double **matrix = calloc(rows, sizeof(double*));

    if (matrix == NULL) {
        printf("/ERROR/ MEMORY ALLOCATION FAILED");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*) calloc(cols, sizeof(double));
        if (matrix[i] == NULL) {
            
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            printf("/ERROR/ MEMORY ALLOCATION FAILED");
            free(matrix);
            exit(1);
        }
    }
    return matrix;
}
/*
* Description: Deallocates (frees) space for a matrix
* Parameters:  
*   - double **matrix: The matrix that will be deallocated
*   - int rows: the number of rows for the matrix
* Return: void
*/
void freeMatrix(double **matrix, int rows) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}
/*
* Description: Computes matrix addition between two matricies A and B
* Parameters:  
*   - double **A: Matrix A
*   - double **B: Matrix B
*   - int nA: the number of rows for matrix A
*   - int mA: the number of columns for matrix A
*   - int nB: the number of rows for matrix B
*   - int mB: the number of column for matrix B
* Return: double** C, the resulting matrix A + B 
*/
double** addMatrices(double **A, double **B, int nA, int mA, int nB, int mB) {

    if (nA != nB || mA != mB) {
        printf("/ERROR/ Matrix ADDITION REQUIRES SAME MATRIX DIMENSIONS\n");
        return NULL;
    }

    double **C = allocateMatrix(nA, mA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}
/*
* Description: Computes matrix subtraction between two matricies A and B
* Parameters:  
*   - double **A: Matrix A
*   - double **B: Matrix B
*   - int nA: the number of rows for matrix A
*   - int mA: the number of columns for matrix A
*   - int nB: the number of rows for matrix B
*   - int mB: the number of column for matrix B
* Return: double** C, the resulting matrix A - B 
*/
double** subtractMatrices(double **A, double **B, int nA, int mA, int nB, int mB) {
    
    if (nA != nB || mA != mB) {
        printf("/ERROR/ Matrix SUBTRACTION REQUIRES SAME MATRIX DIMENSIONS\n");
        return NULL;
    }
            
    double **C = allocateMatrix(nA, mA);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}
/*
* Description: Computes matrix multiplication between two matricies A and B
* Parameters:  
*   - double **A: Matrix A
*   - double **B: Matrix B
*   - int nA: the number of rows for matrix A
*   - int mA: the number of columns for matrix A
*   - int nB: the number of rows for matrix B
*   - int mB: the number of column for matrix B
* Return: double** C: the resulting matrix A * B 
*/
double** multiplicationMatrices(double **A, double **B, int nA, int mA, int nB, int mB) {

    if (mA != nB) {
        printf("/ERROR/ INVALID MATRIX DIMENSIONS\n");
        return NULL;
    }

    double **C = allocateMatrix(nA, mB);
    for (int i = 0; i < nA; i++)
        for (int j = 0; j < mB; j++) {
            double sum = 0.0;
            for (int k = 0; k < mA; k++)
                sum += A[i][k] * B[k][j];
            C[i][j] = sum;
        }

    return C;
}
/*
* Description: Calculates the transpose of a matrix
* Parameters:  
*   - double **A: Matrix A
*   - int nA: the number of rows for matrix A
*   - int mA: the number of columns for matrix A
* Return: double** C: a pointer to the new transposed matrix
*/
double** transposeMatrices(double **A, int nA, int mA) {

    double **C = allocateMatrix(mA,nA);

    for (int i = 0; i < nA; i++) 
        for (int j = 0; j < mA; j++)
            C[j][i] = A[i][j];

    return C;
}
/*
* Description: Uses gauss elimination to Solve Ax + B matrix expressions where A is a square matrix
* Parameters:  
*   - double **A: the matrix multiplied by x 
*   - double **B: the solution matrix
*   - int nA: the number of rows for matrix A
*   - int mA: the number of columns for matrix A
*   - int nB: the number of rows for matrix B
*   - int mB: the number of column for matrix B
* Return: double** x: the resulting matrix x  
*/
double** solveAxB(double **A, double **B, int nA, int mA, int nB, int mB) {

    //Check inputs
    if (nA != nB || mB != 1) {
        printf("/ERROR/ INVALID MATRIX DIMENSIONS\n");
        return NULL;
    }
    if (nA != mA) {
        printf("/ERROR/ MATRIX MUST BE A SQUARE\n");
        return NULL; 
    }

    double **x = allocateMatrix(mA, 1);

    //Gauss Elimination
    for (int i = 0; i < nA - 1; i++) {
    
        int maxRow = i;
        for (int k = i + 1; k < nA; k++) {
            if (absDouble((double) A[k][i]) > absDouble((double) A[maxRow][i])) {
                maxRow = k;
            }
        }
        if (maxRow != i) {
            swapRows(A, i, maxRow);
            swapRows(B, i, maxRow);
        }

        if (absDouble((double) A[i][i]) < 1e-9) {
            printf("MATRIX HAS NO SOLUTIONS OR INFINITE SOLUTIONS\n");
            return NULL;
        }

        double pivot = A[i][i];
        for (int j = i; j < mA; j++) {
            A[i][j] /= pivot;
        }
        B[i][0] /= pivot;

        for (int k = i + 1; k < nA; k++) {
            double factor = A[k][i];
            for (int j = i; j < mA; j++) {
                A[k][j] -= A[i][j] * factor;
            }
            B[k][0] -= B[i][0] * factor;
        }
    }

    //Last Check for no solutions
    for (int i = 0; i < nA; i++)
        if (absDouble((double) A[i][i]) < 1e-9) {
            printf("MATRIX HAS NO SOLUTIONS OR INFINITE SOLUTIONS\n");
            return NULL;
        }

    //Back Substitution to find x
    for (int i = nA - 1; i >= 0; i--) {
        double soln = B[i][0];
        for (int k = i + 1; k < mA; k++) {
            soln -= (x[k][0] * A[i][k]);
        }
        x[i][0] = soln / A[i][i];
    }

    return x;
}
