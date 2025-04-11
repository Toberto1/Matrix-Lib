#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillRandom(double **matrix, int rows, int cols);
void printMatrix(double **matrix, int rows, int cols);
void swapRows(double** matrix, int row1, int row2);
double absDouble(double num);

#endif