#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct vertex {
    int data;
    vertex *left;
    vertex *right;
} *root;

void print_mas(int *A, int n);
void bubble_sort(int *A, int n);
void obhod_left_to_right(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
vertex *ISPD(int L, int R, int *A);
void fill_rand(int *A, int n);

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int n = 100;
    A = (int *)malloc(n * sizeof(int));
    srand(time(0));
    fill_rand(A, 100);
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, 100);
    printf("\n");
    bubble_sort(A, 100);
    printf("Отсортированный массив: ");
    print_mas(A, 100);
    printf("\n");
    root = ISPD(0, 99, A);
    printf("Обход слеав направо: ");
    obhod_left_to_right(root);
    printf("\n\n");
    int size = size_tree(root);
    int sum = sum_tree(root);
    int height = height_tree(root);
    int slw = sum_len_way(root, 1);
    printf("| Размер  |  Сумма  |  Высота |Ср.высота|\n");
    printf("|%9d|%9d|%9d|%9.2f|", size, sum, height, slw / (float)size);
    return 0;
}

void obhod_left_to_right(vertex *p) {
    if (p != NULL) {
        obhod_left_to_right(p->left);
        printf(" %d ", p->data);
        obhod_left_to_right(p->right);
    }
}

int size_tree(vertex *p) {
    int n;
    if (p == NULL) {
        n = 0;
    } else {
        n = 1 + size_tree(p->left) + size_tree(p->right);
    }
    return n;
}
int sum_tree(vertex *p) {
    int s;
    if (p == NULL) {
        s = 0;
    } else {
        s = p->data + sum_tree(p->left) + sum_tree(p->right);
    }
    return s;
}
int height_tree(vertex *p) {
    int h;
    if (p == NULL) {
        h = 0;
    } else {
        h = 1 + std::max(height_tree(p->left), height_tree(p->right));
    }
    return h;
}
int sum_len_way(vertex *p, int l) {
    int s;
    if (p == NULL) {
        s = 0;
    } else {
        s = l + sum_len_way(p->left, l + 1) + sum_len_way(p->right, l + 1);
    }
    return s;
}

vertex *ISPD(int L, int R, int *A) {
    if (L > R)
        return NULL;
    else {
        int m = ceil((L + R) / 2);
        vertex *p = (vertex *)malloc(sizeof(vertex));
        p->data = A[m];
        p->left = ISPD(L, m - 1, A);
        p->right = ISPD(m + 1, R, A);
        return p;
    }
}
void fill_rand(int *A, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % (2 * n + 1);
    }
}
void print_mas(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}
void bubble_sort(int *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[j] < A[j - 1]) {
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
            }
        }
    }
}
