#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Please enter 2 arguments.\n Ex: Lex <input file> <output file>\n");
        return 1;
    }

    //char garbage[10];

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if (input == NULL){

        fprintf(stderr, "Input file does not exist.\n");
        return 1;
    }

    int size, a_entry, b_entry;
    int garb = 0;
    garb = fscanf(input, "%d %d %d\n", &size, &a_entry, &b_entry);
    //printf("Read: %d %d %d\n",size, a_entry, b_entry);

    Matrix A = newMatrix(size);
    Matrix B = newMatrix(size);


    
    int i, j;
    double val;
    //printf("----------\n");
    for(int c = 0; c < a_entry; c++){
        garb = fscanf(input, "%d %d %lf\n", &i,&j,&val);
        //printf("Read: %d %d %f\n",i,j,val);
        changeEntry(A, i, j, val);
    }

    //fgets(garbage, 10, input);
    //printf("----------\n");
    for(int c = 0; c < b_entry; c++){
        garb = fscanf(input, "%d %d %lf\n", &i,&j,&val);
        //printf("Read: %d %d %f\n",i,j,val);
        changeEntry(B, i, j, val);
    }
    //A
    fprintf(output, "A has %d non-zero entries:\n", a_entry);
    printMatrix(output, A);
    //printf("Done printing A\n");

    //B
    fprintf(output, "\nB has %d non-zero entries:\n", b_entry);
    printMatrix(output, B);
    //printf("Done printing B\n");

    //(1.5)*A
    Matrix operation = scalarMult(1.5, A);
    fprintf(output, "\n(1.5)*A =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing 1.5*A\n");

    //A+B
    operation = sum(A,B);
    fprintf(output, "\nA+B =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing A+B\n");

    //A+A
    operation = sum(A,A);
    fprintf(output, "\nA+A =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing A+A\n");

    //B-A
    operation = diff(B,A);
    fprintf(output, "\nB-A =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing B-A\n");

    //A-A
    operation = diff(A,A);
    fprintf(output, "\nA-A =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing A-A\n");

    //Transpose
    operation = transpose(A);
    fprintf(output, "\nTranspose(A) =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing Transpose\n");

    //A*B
    operation = product(A,B);
    fprintf(output, "\nA*B =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing A*B\n");

    //B*B
    operation = product(B,B);
    fprintf(output, "\nB*B =\n");
    printMatrix(output, operation);
    freeMatrix(&operation);
    //printf("Done printing B*B\n");

    fclose(input);
    fclose(output);
    freeMatrix(&A);
    freeMatrix(&B);

    garb = garb;
    return 0;
}