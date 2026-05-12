#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define matLim 1000
#define int_max 2147483647
#define int_min -2147483648
//err codes:
//2= row/col value is invalid
//3= matrices' sizes differ
//4 = unable to create matrix
//5 = sum overflow int
int** matAdd(int** A, int** B, int row1, int col1, int row2, int col2, int* err) {
    if (err == NULL) return NULL;
    *err = 0;
    if (!A) return B;
    if (!B) return A;
    if (row1 < 1 || row1 > matLim) {
        *err = 2;
        return NULL;
    }
    if (row2 < 1 || row2 > matLim) {
        *err = 2;
        return NULL;
    }
    if (col1 < 1 || col1 > matLim) {
        *err = 2;
        return NULL;
    }
    if (col2 < 1 || col2 > matLim) {
        *err = 2;
        return NULL;
    }
    if (row1 != row2 || col1 != col2) {
        *err = 3;
        return NULL;
    }
    int** newMat = createMatrix(row1, col1, 0, 0, err);
    if (*err != 0) {
        *err = 4;
        return NULL;
    }
    for (int i = 0; i < row1; i++) {
        for (int j = 0; j < col1; j++) {
            int valA = 0;
            int valB = 0;

            if (A[i] != NULL) valA = A[i][j];
            if (B[i] != NULL) valB = B[i][j];
            long long val = (long long)valA + valB;
            if (val > int_max || val < int_min) {
                *err = 5;
                int resErr;
                newMat = freeMatrix(newMat, row1, &resErr);
                return NULL;
            }
            newMat[i][j] = val;
        }
    }
    return newMat;
}
int main()
{
    // int err;

    // int** A = createMatrix(4, 2, 0, 5, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(A, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    // int** B = createMatrix(4, 2, 0, 8, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(B, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    //null in a
    //free(A[1]);
    //A[1] = NULL;
    //int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    //if (err == 0) {
    //    int errPrint = printMatrix(C, 4, 2);
    //    if (errPrint != 0) printf("Print error");
    //    freeMatrix(C, 4);
    //}
    //else {
    //    printf("Error code: %d\n", err);
    //}

    ////null in b
    //free(B[2]);
    //B[2] = NULL;
    //int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    //if (err == 0) {
    //    printf("Sum result:\n");
    //    int errPrint = printMatrix(C, 4, 2);
    //    if (errPrint != 0) printf("Print error");
    //    freeMatrix(C, 4);
    //}
    //else {
    //    printf("Error code: %d\n", err);
    //}

    //null in both
    //free(B[1]);
    //B[1] = NULL;
    //free(A[0]);
    //A[0] = NULL;
    //int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    //if (err == 0) {
    //    printf("Sum result (different NULL rows):\n");
    //    int errPrint = printMatrix(C, 4, 2);
    //    if (errPrint != 0) printf("Print error");
    //    freeMatrix(C, 4);
    //}
    //else {
    //    printf("Error code: %d\n", err);
    //}
    //
    //
    // all rows in a are null
    //for (int i = 0; i < 4; i++) {
    //    if (A[i] != NULL) {
    //        free(A[i]);
    //        A[i] = NULL;
    //    }
    //}
    //int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    //if (err == 0) {
    //    printf("Sum result (all A rows NULL):\n");
    //    int errPrint = printMatrix(C, 4, 2);
    //    if (errPrint != 0) printf("Print error");
    //    freeMatrix(C, 4);
    //}
    //else {
    //    printf("Error code: %d\n", err);
    //}

    //all rows are not null
    //int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    //if (err == 0) {
    //    printf("Normal sum result:\n");
    //    int errPrint = printMatrix(C, 4, 2);
    //    if (errPrint != 0) printf("Print error");
    //    freeMatrix(C, 4);
    //}
    //else {
    //    printf("Error code: %d\n", err);
    //}


    // //int overflow
    // int** A = createMatrix(4, 2, 2147483647, 2147483647, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(A, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    // int** B = createMatrix(4, 2, 0, 8, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(B, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");
    // int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(C, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    // correct sum
    // int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(C, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    // A is null
    // int** C = matAdd(NULL, B, 4, 2, 4, 2, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(C, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    // //B is null
    // int** C = matAdd(A, NULL, 4, 2, 4, 2, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(C, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    //incorrect row/col value
    // int** C = matAdd(A, B, -4, 222222222222, 34, 22, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(C, 4, 2);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");

    // freeMatrix(A, 4);
    // freeMatrix(B, 4);

    return 0;
}
