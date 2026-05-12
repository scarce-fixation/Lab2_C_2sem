#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define matLim 1000
#define int_max 2147483647
#define int_min -2147483648
//err codes:
// 1 = matrix is null
//2=too big or too small rows/cols parametr
//4= Unable to create matrix
int** transponse(int** A, int row, int col, int* err) {
    if (err == NULL) return NULL;
    *err = 0;
    if (!A) {
        *err = 1;
        return NULL;
    }
    if (row < 1 || row > matLim) {
        *err = 2;
        return NULL;
    }
    if (col < 1 || col > matLim) {
        *err = 2;
        return NULL;
    }
    int errCreate;
    int** newMat = createMatrix(col, row, 0, 0, &errCreate);
    if (errCreate != 0) {
        *err = 4;
        return NULL;
    }
    for (int i = 0; i < row; i++) {
        if (A[i]) {
            for (int j = 0; j < col; j++) {
                newMat[j][i] = A[i][j];
            }
        }
    }
    freeMatrix(A, row);
    return newMat;
}
int main()
{
    int rows = 4;
    int cols = 3;
    int minValue = 0;
    int maxValue = 1;
    int err;
     int** matrix = createMatrix(rows, cols, minValue, maxValue, &err);
     if (err == 0) {
         int errPrint = printMatrix(matrix, rows, cols);
         if (errPrint != 0) printf("Print error");
     }
     else printf("createMatrix error");
     err = -1;

    //null in matrix
    //free(matrix[2]);
    //matrix[2] = NULL;
    // matrix = transponse(matrix, 4, 3, &err);
    // if (err == 0) {
    //     printMatrix(matrix, 3, 4);
    // }
    // else printf("transponse error");


    // correct transponse
    // matrix = transponse(matrix, 4, 3, &err);
    // if (err == 0) {
    //     printMatrix(matrix, 3, 4);
    // }
    // else printf("transponse error");

    // // incorrect row/col value
    // matrix = transponse(matrix, -4, -3, &err);
    // if (err == 0) {
    //     printMatrix(matrix, 3, 4);
    // }
    // else printf("transponse error");

    // // matrix is null
    // matrix = transponse(NULL, 4, 3, &err);
    // if (err == 0) {
    //     printMatrix(matrix, 3, 4);
    // }
    // else printf("transponse error");

    // // err is null
    // matrix = transponse(matrix, 4, 3, NULL);
    // if (err == 0) {
    //     printMatrix(matrix, 3, 4);
    // }
    // else printf("transponse error");

    // // 1*n transponse
    // matrix = transponse(matrix, 1, 3, &err);
    // if (err == 0) {
    //     printMatrix(matrix, 3, 1);
    // }
    // else printf("transponse error");

    // n*1 transponse
    // matrix = transponse(matrix, 4, 1, &err);
    // if (err == 0) {
    //     printMatrix(matrix, 1, 4);
    // }
    // else printf("transponse error");

    //big transponse
    //int** matrix = createMatrix(100, 65, minValue, maxValue, &err);
    //if (err == 0) {
    //    int errPrint = printMatrix(matrix, 100, 65);
    //    if (errPrint != 0) printf("Print error");
    //}
    //else printf("createMatrix error");
    //err = -1;
    //matrix = transponse(matrix, 100, 65, &err);
    //if (err == 0) {
    //    printMatrix(matrix, 65, 100);
    //}
    //else printf("transponse error");

    return 0;
}
