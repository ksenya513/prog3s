#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *gen_rand_array(int size, int maxValue);
void print(int *arr);
int **gen_rand_matrix(int size, int maxValue);
void print_matrix(int **matrix);

int main() {
    printf("zadanie1\n");
    srand(time(0));
    int size1 = rand() % 10;
    int max = 100;
    int *arr = gen_rand_array(size1, max);
    print(arr);
    printf("\n");
    printf("zadanie2\n");
    int size2 = rand() % 10 + 1;
    int **matrix = gen_rand_matrix(size2, max);
    print_matrix(matrix);
    for (int i = 0; i <= size2; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(arr);
}
int *gen_rand_array(int size, int maxValue) {
    int *A = (int *)malloc(size * sizeof(int));
    A[0] = size;
    srand(time(0));
    for (int i = 1; i < size; i++) {
        A[i] = rand() % (maxValue + 1);
    }
    return A;
}
void print(int *arr) {
    int size = arr[0];
    if (size > 0) {
        printf("%d: ", size - 1);
    } else {
        printf("%d: ", size);
    }
    for (int i = 1; i < size; i++) {
        printf("%2d ", arr[i]);
    }
    printf("\n");
}
int **gen_rand_matrix(int size, int maxValue) {
    int **A = (int **)malloc(size * sizeof(int *));
    A[0] = (int *)malloc(sizeof(int));
    A[0][0] = size;
    for (int i = 1; i < size; i++) {
        int sizestr = rand() % 10 + 1;
        A[i] = (int *)malloc(sizestr * sizeof(int));
        A[i][0] = sizestr;
        for (int j = 1; j < sizestr; j++) {
            A[i][j] = rand() % (maxValue + 1);
        }
    }
    return A;
}
void print_matrix(int **matrix) {
    int size = matrix[0][0];
    if (size > 0) {
        printf("%d\n", size - 1);
    } else {
        printf("%d\n", size);
    }
    for (int i = 1; i < size; i++) {
        int sizestr = matrix[i][0];
        if (sizestr > 0) {
            printf("%d:  ", sizestr - 1);
        } else {
            printf("%d:  ", sizestr);
        }
        for (int j = 1; j < sizestr; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}
