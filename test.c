#include "myAO.h"
#include "utility.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));

    //Check validity of arguments inputted and assign variables to console inputs

    if (argc < 5) {
        printf("/ERROR/ INVALID ARGUMENTS\n");
        return 1;
    }

    int printFlag = atoi(argv[1]); 

    if (printFlag != 1 && printFlag != 0) {
        printf("/ERROR/ INVALID PRINT FLAG\n");
        return 1;
    }

    char op = argv[2][0];

    if (op != '*' && op != '+' && op != '-' && op != 's' && op != 'T') {
        printf("/ERROR/ INVALID OPERATION\n");
        return 1;
    }

    int nA = atoi(argv[3]);  
    int mA = atoi(argv[4]);

    //Check for invalid matrix dimensions for matrix A
    if (nA <= 0 || mA <= 0) {
        printf("/ERROR/ MATRIX DIMENSIONS MUST BE A POSITIVE INTEGER\n");
        return 1;
    }   
    
    //Create matricies

    double **A = allocateMatrix(nA,mA);
    fillRandom(A,nA,mA);

    int nB;
    int mB;
    double **B = NULL;
    
    //Only allocate memory for matrix B if its for specific operations
    if (op == '*' || op == '+' || op == '-' || op == 's') { 
        if (argc != 7) {
            printf("/ERROR/ INVALID ARGUMENTS\n");
            freeMatrix(A,nA);
            return 1;
        }  
        nB = atoi(argv[5]); 
        mB = atoi(argv[6]);
        B = allocateMatrix(nB,mB);
        fillRandom(B,nB,mB);
    } else if (op == 'T') {
        if (argc != 5) {
            printf("/ERROR/ INVALID ARGUMENTS\n");
            freeMatrix(A,nA);
            return 1;
        }   
    }

    //Check for invalid matrix dimensions for matrix B
    if (B != NULL && (nB <= 0 || mB <= 0)) {
        printf("/ERROR/ MATRIX DIMENSIONS MUST BE A POSITIVE INTEGER\n");
        freeMatrix(B,nB);
        return 1;
    }   

    //Print input matricies
    if (printFlag == 1) {
        printf("\nMatrix A:\n---\n");
        printMatrix(A,nA,mA);
        printf("---\n");
        if (B != NULL) {
            printf("Matrix B:\n---\n");
            printMatrix(B,nB,mB);
            printf("---\n");
        }
    }

    //Init resulting matrix and its dimensions
    double **result = NULL;
    int nR = 0;
    int mR = 0;

    //Compute the resulting matrix
    if (op == '+') {
        result = addMatrices(A, B, nA, mA, nB, mB);
        nR = nA;
        mR = mA;
    } else if (op == '-') {
        result = subtractMatrices(A, B, nA, mA, nB, mB);
        nR = nA;
        mR = mA;
    } else if (op == '*') {
        result = multiplicationMatrices(A, B, nA, mA, nB, mB);
        nR = nA;
        mR = mB;
    } else if (op == 'T') {
        result = transposeMatrices(A, nA, mA);
        nR = mA;
        mR = nA;
    } else if (op == 's') {
        result = solveAxB(A, B, nA, mA, nB, mB);
        nR = mA;
        mR = 1;
    } 

    //Abort if resulting matrix calculation failed
    if (result == NULL) {
        freeMatrix(A,nA);
        freeMatrix(B,nB);
        return 1;
    }

    //Print resulting matrix
    if (printFlag == 1 && result != NULL) {        
        switch (op) {
            case '+': 
            case '-':
            case '*':
                printf("Resulting Matrix A %c B:\n---\n",op); break;
            case 'T':
                printf("Resulting Matrix from the Transpose of A:\n---\n"); break;
            case 's':
                printf("Resulting Matrix 'x' from the solution to the system Ax = B\n---\n"); break;
        }
        printMatrix(result,nR,mR);
        printf("---\n");
    }

    //Deallocate all matricies
    freeMatrix(result,nR);
    freeMatrix(A,nA);
    freeMatrix(B,nB);

    return 0;
}