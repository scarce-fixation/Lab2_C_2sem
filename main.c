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
int** createMatrix( int rows,  int cols, long long minValue, long long maxValue, int* err) {
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
int freeMatrix(int** matrix, int rows) {
    if (matrix == NULL) {
        return 1;
    }
    if(rows < 1 || rows > matLim) return 2;

    for (int i = 0; i < rows; i++) {
        if (matrix[i] != NULL) {
            free(matrix[i]);
        }
    }

    free(matrix);
    return 0;
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
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
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
        for (int j = 0; j < col; j++) {
            newMat[j][i] = A[i][j];
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
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &err);
    // if (err == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     if (errPrint != 0) printf("Print error");
    // }
    // else printf("createMatrix error");
    // err = -1;

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
    int** matrix = createMatrix(100, 65, minValue, maxValue, &err);
    if (err == 0) {
        int errPrint = printMatrix(matrix, 100, 65);
        if (errPrint != 0) printf("Print error");
    }
    else printf("createMatrix error");
    err = -1;
    matrix = transponse(matrix, 100, 65, &err);
    if (err == 0) {
        printMatrix(matrix, 65, 100);
    }
    else printf("transponse error");

    return 0;
}
