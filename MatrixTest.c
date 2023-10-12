#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"

int main() {
    Matrix A = newMatrix(2);

    changeEntry(A, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 2, 1, 3);
    changeEntry(A, 2, 2, 4);

    Matrix B = newMatrix(2);
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 2, 2);
    changeEntry(B, 2, 1, 3);
    changeEntry(B, 2, 2, 4);
    
    Matrix c = product(A,B);
    printMatrix(stdout,c);



    freeMatrix(&A);
    return 0;
}