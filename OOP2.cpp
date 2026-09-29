#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **gen_rand_matrix(int size, int maxValue);
void print_N_matrix(int **matrix, int size);
void print_rand_matrix(int **matrix, int size);
int **gen_N_matrix(int size, int maxValue);
void print_D(int *D, int size);

void rightDiagonals(int **matrix, int *arr, int size);
void leftDiagonals(int **matrix, int *arr, int size);
void spiralFromCenter(int **matrix, int size, int *arr);
void spiral_start(int **matrix, int *D, int size);

int main() {
    printf("zadanie1\n");
    srand(time(0));
    int max = 100;
    int size = rand() % 5 + 1;
    int double_size = size * size;

    int **matrix = gen_N_matrix(size, max);
    printf("Исходная матрица %dx%d:\n", size, size);
    print_N_matrix(matrix, size);

    int D[double_size];

    rightDiagonals(matrix, D, size);
    printf("\nПо правым диагоналям: ");
    print_D(D, double_size);

    leftDiagonals(matrix, D, size);
    printf("По лнвым диагоналям: ");
    print_D(D, double_size);

    spiralFromCenter(matrix, size, D);
    printf("По спирали от центра: ");
    print_D(D, double_size);

    spiral_start(matrix, D, size);
    printf("ПО спирали с 1 элемента: ");
    print_D(D, double_size);

    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    printf("\nzadanie2\n");
    int rows = rand() % 5 + 2;
    int **rand_matrix = gen_rand_matrix(rows, max);
    print_rand_matrix(rand_matrix, rows);

    for (int i = 0; i < rows; i++) {
        free(rand_matrix[i]);
    }
    free(rand_matrix);

    return 0;
}

void print_D(int *D, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", D[i]);
    }
    printf("\n");
}

int **gen_N_matrix(int size, int maxValue) {
    int **A = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        A[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            A[i][j] = rand() % (maxValue + 1);
        }
    }
    return A;
}

int **gen_rand_matrix(int size, int maxValue) {
    int **A = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        int sizestr = rand() % 8 + 2;
        A[i] = (int *)malloc((sizestr + 1) * sizeof(int));
        A[i][0] = sizestr;
        for (int j = 1; j <= sizestr; j++) {
            A[i][j] = rand() % (maxValue + 1);
        }
    }
    return A;
}

void print_N_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void print_rand_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        int len = matrix[i][0];
        for (int j = 1; j <= len; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void rightDiagonals(int **matrix, int *arr, int size) {
    int c = 0;
    for (int k = size - 1; k >= 0; k--) {
        int i = 0, j = k;
        while (i < size && j < size) {
            arr[c++] = matrix[i][j];
            i++;
            j++;
        }
    }
    for (int k = 1; k < size; k++) {
        int i = k, j = 0;
        while (i < size && j < size) {
            arr[c++] = matrix[i][j];
            i++;
            j++;
        }
    }
}

void leftDiagonals(int **matrix, int *arr, int size) {
    int c = 0;
    for (int k = 0; k < size; k++) {
        int i = 0, j = k;
        while (i < size && j >= 0) {
            arr[c++] = matrix[i][j];
            i++;
            j--;
        }
    }
    for (int k = 1; k < size; k++) {
        int i = k, j = size - 1;
        while (i < size && j >= 0) {
            arr[c++] = matrix[i][j];
            i++;
            j--;
        }
    }
}
void spiralFromCenter(int **matrix, int size, int *arr) {
    int c = 0;
    int r = (size - 1) / 2;
    int col = (size - 1) / 2;

    arr[c++] = matrix[r][col];

    int step = 1;
    while (c < size * size) {
        for (int i = 0; i < step && c < size * size; i++)
            arr[c++] = matrix[r][++col];
        for (int i = 0; i < step && c < size * size; i++)
            arr[c++] = matrix[++r][col];

        step++;

        for (int i = 0; i < step && c < size * size; i++)
            arr[c++] = matrix[r][--col];
        for (int i = 0; i < step && c < size * size; i++)
            arr[c++] = matrix[--r][col];

        step++;
    }
}
void spiral_start(int **matrix, int *D, int size) {
    int k = 0;
    int top = 0;
    int bottom = size - 1;
    int left = 0;
    int right = size - 1;

    while (k < size * size) {
        for (int j = left; j <= right && k < size * size; j++) {
            D[k++] = matrix[top][j];
        }
        top++;

        for (int i = top; i <= bottom && k < size * size; i++) {
            D[k++] = matrix[i][right];
        }
        right--;
        for (int j = right; j >= left && k < size * size; j--) {
            D[k++] = matrix[bottom][j];
        }
        bottom--;

        for (int i = bottom; i >= top && k < size * size; i--) {
            D[k++] = matrix[i][left];
        }
        left++;
    }
}