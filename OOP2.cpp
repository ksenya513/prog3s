#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **gen_rand_matrix(int size, int maxValue);
void print_N_matrix(int **matrix, int size);
void print_rand_matrix(int **matrix, int size);
int **gen_N_matrix(int size, int maxValue);
void print_D(int *D, int size);

void right_diaginal(int **matrix, int *D, int size);
void left_diaginal(int **matrix, int *D, int size);
void spiral_center(int **matrix, int *D, int size);
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

    right_diaginal(matrix, D, size);
    printf("\nП правым диагоналям: ");
    print_D(D, double_size);

    left_diaginal(matrix, D, size);
    printf("По левым диагоналям: ");
    print_D(D, double_size);

    spiral_center(matrix, D, size);
    printf("По спирали от центра: ");
    print_D(D, double_size);

    spiral_start(matrix, D, size);
    printf("По спирали с 1 элемента: ");
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
        printf("Stroka %d (%d el): ", i + 1, len);
        for (int j = 1; j <= len; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void right_diaginal(int **matrix, int *D, int size) {
    int k = 0;
    for (int start_c = size - 1; start_c >= 0; start_c--) {
        int r = 0;
        int c = start_c;
        while (r < size && c >= 0) {
            D[k] = matrix[r][c];
            k = k + 1;
            r = r + 1;
            c = c - 1;
        }
    }

    for (int start_r = 1; start_r < size; start_r++) {
        int r = start_r;
        int c = size - 1;
        while (r < size && c >= 0) {
            D[k] = matrix[r][c];
            k = k + 1;
            r = r + 1;
            c = c - 1;
        }
    }
}

void left_diaginal(int **matrix, int *D, int size) {
    int k = 0;
    for (int start_c = size - 1; start_c >= 0; start_c--) {
        int r = 0;
        int c = start_c;
        while (r < size && c < size) {
            D[k] = matrix[r][c];
            k = k + 1;
            r = r + 1;
            c = c + 1;
        }
    }

    for (int start_r = 1; start_r < size; start_r++) {
        int r = start_r;
        int c = 0;
        while (r < size && c < size) {
            D[k] = matrix[r][c];
            k = k + 1;
            r = r + 1;
            c = c + 1;
        }
    }
}
void spiral_center(int **matrix, int *D, int size) {
    int k = 0;
    int r = size / 2;
    int c = size / 2;

    D[k] = matrix[r][c];
    k++;

    int step = 1;
    while (k < size * size) {
        // Вправо
        for (int i = 0; i < step; i++) {
            c = c + 1;
            if (r >= 0 && r < size && c >= 0 && c < size) {
                D[k] = matrix[r][c];
                k++;
            }
        }
        // Вниз
        for (int i = 0; i < step; i++) {
            r = r + 1;
            if (r >= 0 && r < size && c >= 0 && c < size) {
                D[k] = matrix[r][c];
                k++;
            }
        }
        step = step + 1;

        // Влево
        for (int i = 0; i < step; i++) {
            c = c - 1;
            if (r >= 0 && r < size && c >= 0 && c < size) {
                D[k] = matrix[r][c];
                k++;
            }
        }
        // Вверх
        for (int i = 0; i < step; i++) {
            r = r - 1;
            if (r >= 0 && r < size && c >= 0 && c < size) {
                D[k] = matrix[r][c];
                k++;
            }
        }
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