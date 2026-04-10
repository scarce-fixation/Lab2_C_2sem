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
int main()
{
    //  Нормальная матрица 4x3, диапазон [2, 5]
    // int rows = 4;
    // int cols = 3;
    // int minValue = 2;
    // int maxValue = 5;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // rows = -5 (отрицательное значение)
    // int rows = -5;
    // int cols = 3;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // cols = 0 (недопустимое значение)
    // int rows = 3;
    // int cols = 0;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // cols = 2000 (превышает matLim)
    // int rows = 3;
    // int cols = 2000;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // maxValue > INT_MAX (2147483648)
    // int rows = 3;
    // int cols = 3;
    // int minValue = 0;
    // long long maxValue = 2147483648LL;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // minValue < INT_MIN (-2147483649)
    // int rows = 3;
    // int cols = 3;
    // long long minValue = -2147483649LL;
    // int maxValue = 0;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // minValue = maxValue = 42
    // int rows = 2;
    // int cols = 2;
    // int minValue = 42;
    // int maxValue = 42;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // Максимальная матрица 1000x1000
    // int rows = 1000;
    // int cols = 1000;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, rows, cols);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // printMatrix с NULL (матрица не создается)
    // int rows = 3;
    // int cols = 3;
    // int errPrint = printMatrix(NULL, rows, cols);
    // if(errPrint != 0) printf("Matrix print error: %d", errPrint);

    // printMatrix с некорректными rows
    // int rows = 3;
    // int cols = 3;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errPrint = printMatrix(matrix, 0, cols);
    //     int errFree = freeMatrix(matrix, rows);
    //     if(errPrint != 0) printf("Matrix print error: %d", errPrint);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    // }
    // else printf("Matrix create error: %d", errCreate);

    // freeMatrix с NULL
    // int rows = 3;
    // int errFree = freeMatrix(NULL, rows);
    // if(errFree != 0) printf("Matrix free error: %d", errFree);

    // freeMatrix с некорректными rows
    // int rows = 3;
    // int cols = 3;
    // int minValue = 0;
    // int maxValue = 100;
    // int errCreate;
    // int** matrix = createMatrix(rows, cols, minValue, maxValue, &errCreate);
    // if (errCreate == 0) {
    //     int errFree = freeMatrix(matrix, 0);
    //     if(errFree != 0) printf("Matrix free error: %d", errFree);
    //     freeMatrix(matrix, rows);
    // }
    // else printf("Matrix create error: %d", errCreate);
}