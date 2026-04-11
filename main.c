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
    for(int i =0; i < row1; i++){
      for(int j=0; j < col1; j++){
        long long val = A[i][j] + B[i][j];
        if(val > int_max || val < int_min){
          *err = 5;
          return NULL;
}
        newMat[i][j] = val;
}
}
    return newMat;
}
int main()
{
    int err;
    int** A = createMatrix(4, 2, 0, 8, &err);
    if (err == 0) {
        int errPrint = printMatrix(A, 4, 2);
        if (errPrint != 0) printf("Print error");
    }
    else printf("createMatrix error");

    int** B = createMatrix(4, 2, 0, 8, &err);
    if (err == 0) {
        int errPrint = printMatrix(B, 4, 2);
        if (errPrint != 0) printf("Print error");
    }
    else printf("createMatrix error");

    int** C = matAdd(A, B, 4, 2, 4, 2, &err);
    if (err == 0) {
        int errPrint = printMatrix(C, 4, 2);
        if (errPrint != 0) printf("Print error");
    }
    else printf("createMatrix error");


    return 0;
}
