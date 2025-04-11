#include "utility.h"

void fillRandom(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = (rand() % 21) - 10; // Generates values from -10 to +10
}

void printMatrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%6.2f ", matrix[i][j]);
        printf("\n");
    }
}
/*
* Description: Swaps two rows of a matrix
* Parameters:  
*   - double **matrix: The matrix that will have a row swap
*   - int row1: the first row that will be swapped
*   - int row2: the second row that will be swapped with the first
* Return: void
*/
void swapRows(double** matrix, int row1, int row2) {
    double* temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;
}
/*
* Description: Performs the absolute function on a double
* Parameters:  
*   - double num: The input number to the absolute function
* Return: double num: the absoulte value of the input
*/
double absDouble(double num) {
    if (num < 0) return -num;
        else return num;
}