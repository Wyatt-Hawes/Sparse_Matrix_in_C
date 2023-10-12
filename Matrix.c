#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"


typedef struct MatrixObj{

    List* rows;

    int size;
    int non_zero_elements;


} MatrixObj;


Entry newEntry(int col, double val){
    Entry e = malloc(sizeof(EntryObj));
    e->col = col;
    e->val = val;

    return e;
}

Matrix newMatrix(int n){
    Matrix m;
    m = malloc(sizeof(MatrixObj));
    assert(m != NULL);

    m->size = n;
    m->rows = calloc(n + 1, sizeof(List));

    for(int i = 0; i < m->size + 1; i++){
        m->rows[i] = newList();
    }
    m->non_zero_elements = 0;
    return m;
}

void freeMatrix(Matrix* pM){
    for(int i = 0; i < (* pM)->size + 1; i++){
        freeList(&((*pM)->rows[i]));
    }
    free((*pM)->rows);

    free((*pM));
    
}

int size(Matrix M){
    if( M==NULL ){
      printf("Matrix Error: calling size() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
   }

    return M->size;
}

int NNZ(Matrix M){
    if( M==NULL ){
      printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }

    return M->non_zero_elements;
}

int equals(Matrix A, Matrix B){
    if( A==NULL || B == NULL ){
      printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }

    if(A == B){
        return 1;
    }

    int az = A->non_zero_elements;
    int bz = B->non_zero_elements;

    if(A->size != B->size){
        return 0;
    }

    if(az != bz){
        return 0;
    }



    for(int i = 1; i < A->size + 1; i++){
        if(length(A->rows[i]) != length(B->rows[i])){
            return 0;
        }
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        for(int j = 0; j < length(A->rows[i]); j++){
            //printf("C:%d\n", index(A->rows[i]));
            if(( ((Entry)get(A->rows[i]))->col != ((Entry)get(B->rows[i]))->col)         ||     ( ((Entry)get(A->rows[i]))->val != ((Entry)get(B->rows[i]))->val)   ){
                return 0;
            }else{
                moveNext(A->rows[i]);
                moveNext(B->rows[i]);
            }
        }
    }

    return 1;
}

void makeZero(Matrix M){
    for(int i = 0; i < M->size + 1; i++){
        clear(M->rows[i]);
    }
    M->non_zero_elements = 0;
    return;
}


void changeEntry(Matrix M, int i, int j, double x){
    if( M==NULL ){
      printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    
    if((i < 1) || (i > M->size)){
        printf("Matrix Error: calling changeEntry() on invalid i(%d)size(%d)\n", i,M->size);
        exit(EXIT_FAILURE);
    }
    if((j < 1)|| (j > M->size)){
        printf("Matrix Error: calling changeEntry() on invalid j(%d) size(%d)\n", j,M->size);
        exit(EXIT_FAILURE);
    }
    Entry e;

    moveFront(M->rows[i]);

    while(index(M->rows[i]) > -1){

            
        if(((Entry)get(M->rows[i]))->col == j){
            if(x==0){
                delete(M->rows[i]);
                M->non_zero_elements--;
                return;
            }
            e = newEntry(j,x);
            free(get(M->rows[i]));
            set(M->rows[i], e);
            return;
        }
        if(((Entry)get(M->rows[i]))->col > j){
            if(x == 0){
                return;
            }
            e = newEntry(j,x);
            M->non_zero_elements++;
            insertBefore(M->rows[i], e);
            return;
        }

        moveNext(M->rows[i]);
    }
    if(x == 0){
        return;
    }
    e = newEntry(j,x);
    M->non_zero_elements++;
    append(M->rows[i], e);
    return;
}

Matrix copy(Matrix A){
    Matrix cp = newMatrix(A->size);
    
    for(int i = 0; i < A->size + 1; i ++){
        moveFront(A->rows[i]);
        while(index(A->rows[i]) > -1){
            Entry e = get(A->rows[i]);
            changeEntry(cp, i, e->col, e->val);
            moveNext(A->rows[i]);
        }
    }

    return cp;

}

Matrix transpose(Matrix A){
    Matrix tp = newMatrix(A->size);

    for(int i = 0; i < A->size + 1; i ++){
        moveFront(A->rows[i]);
        while(index(A->rows[i]) > -1){
            Entry e = get(A->rows[i]);
            changeEntry(tp, e->col, i, e->val);
            moveNext(A->rows[i]);
        }
    }

    return tp;
}

Matrix scalarMult(double x, Matrix A){
    Matrix cp; 
    if (x == 1){
        cp = copy(A);
        return cp;
    }
    cp = newMatrix(A->size);
    if(x == 0){
        return cp;
    }
    for(int i = 0; i < A->size + 1; i ++){
        moveFront(A->rows[i]);
        while(index(A->rows[i]) > -1){
            Entry e = get(A->rows[i]);
            changeEntry(cp, i, e->col, (e->val) * x);
            moveNext(A->rows[i]);
        }
    }
    return cp;
}

Matrix sum(Matrix A, Matrix B){

    if(A->size != B->size){
        
      printf("Matrix Error: calling sum() on Matrices of different size\n");
      exit(EXIT_FAILURE);
    
    }

    

    Matrix sum1;
    
    if(equals(A,B)){
        sum1 = scalarMult(2,A);
        return sum1;
    }
    
    sum1 = newMatrix(A->size);

    int Acol = 0;
    int Bcol = 0;
    int Aindex = 0,Bindex = 0;
    double Aval = 0, Bval = 0;
    //Acol = ((Entry)get(A->rows[i]))->col;
    //Aval = ((Entry)get(A->rows[i]))->val;

    //Bcol = ((Entry)get(B->rows[i]))->col;
    //Bval = ((Entry)get(B->rows[i]))->val;



    for(int i = 1; i < A->size + 1; i ++){
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        Aindex = index(A->rows[i]);
        Bindex = index(B->rows[i]);
        while(Aindex != -1 || Bindex != -1){
            
            if(Aindex != -1){
                Acol = ((Entry)get(A->rows[i]))->col;
                Aval = ((Entry)get(A->rows[i]))->val;
            }
            if(Bindex != -1){
                Bcol = ((Entry)get(B->rows[i]))->col;
                Bval = ((Entry)get(B->rows[i]))->val;
            }
            //Just A
            if((Bindex == -1) || (Aindex != -1 && Acol < Bcol)){
                changeEntry(sum1, i, Acol,Aval);
                moveNext(A->rows[i]);
                Aindex = index(A->rows[i]);
                Bindex = index(B->rows[i]);
                continue;
            }
            //Just B
            if((Aindex == -1) || (Bindex != -1 && Bcol < Acol)){
                changeEntry(sum1, i, Bcol,Bval);
                moveNext(B->rows[i]);
                Aindex = index(A->rows[i]);
                Bindex = index(B->rows[i]);
                continue;
            }
            //Both
            changeEntry(sum1, i, Acol, Aval + Bval);
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
            Aindex = index(A->rows[i]);
            Bindex = index(B->rows[i]);
            continue;

        }
    }
    return sum1;
}

Matrix diff(Matrix A, Matrix B){
    if(A->size != B->size){
        
      printf("Matrix Error: calling sum() on Matrices of different size\n");
      exit(EXIT_FAILURE);
    
    }

    

    Matrix sum1;
    
    if(equals(A,B)){
        sum1 = newMatrix(A->size);
        return sum1;
    }
    
    sum1 = newMatrix(A->size);

    int Acol = 0;
    int Bcol = 0;
    int Aindex = 0,Bindex = 0;
    double Aval = 0, Bval = 0;
    //Acol = ((Entry)get(A->rows[i]))->col;
    //Aval = ((Entry)get(A->rows[i]))->val;

    //Bcol = ((Entry)get(B->rows[i]))->col;
    //Bval = ((Entry)get(B->rows[i]))->val;



    for(int i = 1; i < A->size + 1; i ++){
        moveFront(A->rows[i]);
        moveFront(B->rows[i]);
        Aindex = index(A->rows[i]);
        Bindex = index(B->rows[i]);
        while(Aindex != -1 || Bindex != -1){
            
            if(Aindex != -1){
                Acol = ((Entry)get(A->rows[i]))->col;
                Aval = ((Entry)get(A->rows[i]))->val;
            }
            if(Bindex != -1){
                Bcol = ((Entry)get(B->rows[i]))->col;
                Bval = ((Entry)get(B->rows[i]))->val;
            }
            //Just A
            if((Bindex == -1) || (Aindex != -1 && Acol < Bcol)){
                changeEntry(sum1, i, Acol, Aval);
                moveNext(A->rows[i]);
                Aindex = index(A->rows[i]);
                Bindex = index(B->rows[i]);
                continue;
            }
            //Just B
            if((Aindex == -1) || (Bindex != -1 && Bcol < Acol)){
                changeEntry(sum1, i, Bcol,(-1 * Bval));
                moveNext(B->rows[i]);
                Aindex = index(A->rows[i]);
                Bindex = index(B->rows[i]);
                continue;
            }
            //Both

            changeEntry(sum1, i, Acol, Aval - Bval);
            moveNext(A->rows[i]);
            moveNext(B->rows[i]);
            Aindex = index(A->rows[i]);
            Bindex = index(B->rows[i]);
            continue;

        }
    }
    return sum1;
}

Matrix product(Matrix A, Matrix b2){
    if(A->size != b2->size){
        
      printf("Matrix Error: calling product() on Matrices of different size (%d vs %d)\n", A->size, b2->size);
      exit(EXIT_FAILURE);
    
    }

    //Getting transpose of Matrix b2 in order to make multiplication easier.
    Matrix B = transpose(b2);

    Matrix prod = newMatrix(A->size);

    

    for(int i = 1; i < A->size + 1; i ++){
        moveFront(A->rows[i]);
        if(index(A->rows[i]) == -1){
            continue;
        }
        for(int j = 1; j < B->size + 1; j++){
            double total = 0;
            moveFront(A->rows[i]);
            moveFront(B->rows[j]);
            while(index(A->rows[i]) != -1 && index(B->rows[j]) != -1){
                //Just A
                if((index(B->rows[j]) == -1) || (index(A->rows[i]) != -1 && ((Entry)get(A->rows[i]))->col < ((Entry)get(B->rows[j]))->col)){
                    //changeEntry(prod, i, ((Entry)get(A->rows[i]))->col,((Entry)get(A->rows[i]))->val);
                    moveNext(A->rows[i]);
                    continue;
                }
                //Just B
                if((index(A->rows[i]) == -1) || (index(B->rows[j]) != -1 && ((Entry)get(B->rows[j]))->col < ((Entry)get(A->rows[i]))->col)){
                    //changeEntry(prod, i, ((Entry)get(B->rows[i]))->col,((Entry)get(B->rows[i]))->val);
                    moveNext(B->rows[j]);
                    continue;
                }

                    total = total + (((Entry)get(A->rows[i]))->val * ((Entry)get(B->rows[j]))->val);
                    moveNext(A->rows[i]);
                    moveNext(B->rows[j]);
                    continue;
            }
            //
            //printf("setting (%d,%d) to %f\n",i,j, total);
            if (total != 0){
                changeEntry(prod, i, j, total);
            }
        }

    }


    freeMatrix(&B);
    return prod;
}

void printMatrix(FILE* out, Matrix m){
    for(int i = 1; i < m->size + 1; i++){
        if(length(m->rows[i]) != 0){
            fprintf(out, "%d: ", i);
        }
        moveFront(m->rows[i]);
        int changed = 0;
        while(index(m->rows[i]) != -1){
            fprintf(out, "(%d, %.1f) ", ((Entry)get(m->rows[i]))->col,((Entry)get(m->rows[i]))->val);
            moveNext(m->rows[i]);
            changed = 1;
        }
        if (changed == 1){
            fprintf(out, "\n");
        }
    }
}