#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define matLim 1000
#define int_max 2147483647
#define int_min -2147483648
//Eror codes:
//0 = success
//1 = bad rows value
//2 = alloc error
//3 = bad cols
//4 = bad minVal
//5 = bad maxVal
//!(above mention) = err is null
int** createMatrix(int rows, int cols, long long minValue, long long maxValue, int* err) {
    if (err == NULL) return NULL;
    srand(time(NULL));
    *err = 0;
    if (rows <= 0 || rows > matLim) {
        *err = 1;
        return NULL;
    }
    if (cols <= 0 || cols > matLim) {
        *err = 3;
        return NULL;
    }
    if (minValue > maxValue) {
        long long temp = minValue;
        minValue = maxValue;
        maxValue = temp;
    }
    if (maxValue > int_max || maxValue < int_min) {
        *err = 5;
        return NULL;
    }
    if (minValue > int_max || minValue < int_min) {
        *err = 4;
        return NULL;
    }
    int** matrix = (int**)malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        *err = 2;
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            *err = 1;
            return NULL;
        }
        for (int j = 0; j < cols; j++) {
            int randValue = minValue + rand() % (maxValue - minValue + 1);
            matrix[i][j] = randValue;
        }
    }
    return matrix;
}
//err codes
//1= matrix null
//2=rows value is invalid
//0=success
void freeMatrix(int*** matrix, int rows, int* err) {
    if (err == NULL) return;
    if (matrix == NULL || *matrix == NULL) {
        *err = 1;
        return;
    }
    if (rows < 1 || rows > matLim) {
        *err = 2;
        return;
    }
    *err = 0;
    for (int i = 0; i < rows; i++) {
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
    }
    free(*matrix);
    *matrix = NULL;
    return;
}
//error codes:
//1=parametr is null
//2=too big or too small rows/cols parametr
int printMatrix(int** matrix, int rows, int cols) {
    if (matrix == NULL) return 1;
    if (rows > matLim || cols > matLim) return 2;
    if (rows < 1 || cols < 1) return 2;
    printf("\nMatrix %dx%d:\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        if (matrix[i] == NULL) {
            printf("NULL\n");
            continue;
        }
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
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
                freeMatrix(&newMat, row1, &resErr);
                return NULL;
            }
            newMat[i][j] = val;
        }
    }
    return newMat;
}
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
    int errFree;
    freeMatrix(&A, row, &errFree);
    return newMat;
}
int main()
{
//base func
    //  Нормальная матрица 4x3, диапазон [2, 5]
     /*int rows = 4;
     int cols = 3;
     int minValue = 2;
     int maxValue = 5;
     int errCreate;
     int errFree;
     int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     if (errCreate == 0) {
         int errPrint = printMatrix(matrix, rows, cols);
         freeMatrix(&matrix, rows, &errFree);
         if(errPrint != 0) printf("Matrix print error: %d", errPrint);
         if(errFree != 0) printf("Matrix free error: %d", errFree);
     }
     else printf("Matrix create error: %d", errCreate);*/

    // rows = -5 (отрицательное значение)
     /*int rows = -5;
     int cols = 3;
     int minValue = 0;
     int maxValue = 100;
     int errCreate;
     int errFree;
     int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     if (errCreate == 0) {
         int errPrint = printMatrix(matrix, rows, cols);
         freeMatrix(&matrix, rows, &errFree);
         if(errPrint != 0) printf("Matrix print error: %d", errPrint);
         if(errFree != 0) printf("Matrix free error: %d", errFree);
     }
     else printf("Matrix create error: %d", errCreate);*/

    // cols = 0 (недопустимое значение)
     /*int rows = 3;
     int cols = 0;
     int minValue = 0;
     int maxValue = 100;
     int errCreate;
     int errFree;
     int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     if (errCreate == 0) {
         int errPrint = printMatrix(matrix, rows, cols);
         freeMatrix(&matrix, rows, &errFree);
         if(errPrint != 0) printf("Matrix print error: %d", errPrint);
         if(errFree != 0) printf("Matrix free error: %d", errFree);
     }
     else printf("Matrix create error: %d", errCreate);*/

    // cols = 2000 (превышает matLim)
     //int rows = 3;
     //int cols = 2000;
     //int minValue = 0;
     //int maxValue = 100;
     //int errCreate;
     //int errFree;
     //int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     //if (errCreate == 0) {
     //    int errPrint = printMatrix(matrix, rows, cols);
     //    freeMatrix(&matrix, rows, &errFree);
     //    if(errPrint != 0) printf("Matrix print error: %d", errPrint);
     //    if(errFree != 0) printf("Matrix free error: %d", errFree);
     //}
     //else printf("Matrix create error: %d", errCreate);

    // maxValue > INT_MAX (2147483648)
     //int rows = 3;
     //int cols = 3;
     //int minValue = 0;
     //long long maxValue = 2147483648LL;
     //int errCreate;
     //int errFree;
     //int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     //if (errCreate == 0) {
     //    int errPrint = printMatrix(matrix, rows, cols);
     //    freeMatrix(&matrix, rows, &errFree);
     //    if(errPrint != 0) printf("Matrix print error: %d", errPrint);
     //    if(errFree != 0) printf("Matrix free error: %d", errFree);
     //}
     //else printf("Matrix create error: %d", errCreate);

    // minValue < INT_MIN (-2147483649)
     //int rows = 3;
     //int cols = 3;
     //long long minValue = -2147483649LL;
     //int maxValue = 0;
     //int errCreate;
     //int errFree;
     //int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     //if (errCreate == 0) {
     //    int errPrint = printMatrix(matrix, rows, cols);
     //    freeMatrix(&matrix, rows, &errFree);
     //    if(errPrint != 0) printf("Matrix print error: %d", errPrint);
     //    if(errFree != 0) printf("Matrix free error: %d", errFree);
     //}
     //else printf("Matrix create error: %d", errCreate);

    // minValue = maxValue = 42
     //int rows = 2;
     //int cols = 2;
     //int minValue = 42;
     //int maxValue = 42;
     //int errCreate;
     //int errFree;
     //int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     //if (errCreate == 0) {
     //    int errPrint = printMatrix(matrix, rows, cols);
     //    freeMatrix(&matrix, rows, &errFree);
     //    if(errPrint != 0) printf("Matrix print error: %d", errPrint);
     //    if(errFree != 0) printf("Matrix free error: %d", errFree);
     //}
     //else printf("Matrix create error: %d", errCreate);

    // Максимальная матрица 1000x1000
     //int rows = 1000;
     //int cols = 1000;
     //int minValue = 0;
     //int maxValue = 100;
     //int errCreate;
     //int errFree;
     //int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     //if (errCreate == 0) {
     //    int errPrint = printMatrix(matrix, rows, cols);
     //    if(errPrint != 0) printf("Matrix print error: %d", errPrint);
     //    freeMatrix(&matrix, rows, &errFree);
     //    if(errFree != 0) printf("Matrix free error: %d", errFree);
     //}
     //else printf("Matrix create error: %d", errCreate);

    // printMatrix с NULL (матрица не создается)
     //int rows = 3;
     //int cols = 3;
     //int errPrint = printMatrix(NULL, rows, cols);
     //if(errPrint != 0) printf("Matrix print error: %d", errPrint);

    // printMatrix с некорректными rows
     //int rows = 3;
     //int cols = 3;
     //int minValue = 0;
     //int maxValue = 100;
     //int errCreate;
     //int errFree;
     //int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
     //if (errCreate == 0) {
     //    int errPrint = printMatrix(matrix, 0, cols);
     //    freeMatrix(&matrix, rows, &errFree);
     //    if(errPrint != 0) printf("Matrix print error: %d", errPrint);
     //    if(errFree != 0) printf("Matrix free error: %d", errFree);
     //}
     //else printf("Matrix create error: %d", errCreate);

    // freeMatrix с NULL
     //int rows = 3;
     //int errFree;
     //freeMatrix(NULL, rows, &errFree);
     //if(errFree != 0) printf("Matrix free error: %d", errFree);

    // freeMatrix с некорректными rows
    // int rows = 3;
    // int cols = 3;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int errFree;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     freeMatrix(&matrix, 0, &errFree);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    //     freeMatrix(&matrix, rows, &errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);


//transponse
    // int rows = 4;
    // int cols = 3;
    // int minValue = 0;
    // int maxValue = 1;
    // int err;
    //  int** matrix = createMatrix(rows, cols, minValue, maxValue, &err);
    //  if (err == 0) {
    //      int errPrint = printMatrix(matrix, rows, cols);
    //      if (errPrint != 0) printf("Print error");
    //  }
    //  else printf("createMatrix error");
    //  err = -1;

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

//freeMatrix(&matrix, rows, &err);

//matAdd

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
    //    freeMatrix(&C, 4, &err);
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
    //    freeMatrix(&C, 4, &err);
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
    //    freeMatrix(&C, 4, &err);
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
    //    freeMatrix(&C, 4, &err);
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
    //    freeMatrix(&C, 4, &err);
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

    // freeMatrix(&A, 4, &err);
    // freeMatrix(&B, 4, &err);

    return 0;
}