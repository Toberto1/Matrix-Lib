#ifndef MYAO_H
#define MYAO_H

#include <stdio.h>
#include <stdlib.h>

double** allocateMatrix(int rows, int cols);
void freeMatrix(double **matrix, int rows);

double** addMatrices(double **A, double **B, int nA, int mA, int nB, int mB);
double** subtractMatrices(double **A, double **B, int nA, int mA, int nB, int mB);

double** multiplicationMatrices(double **A, double **B, int nA, int mA, int nB, int mB);
double** transposeMatrices(double **A, int nA, int mA);
double** solveAxB(double **A, double **B, int nA, int mA, int nB, int mB);

#endif