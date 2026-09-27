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
} *root, *root1, *root2;
int duplicate[3] = {0, 0, 0};

enum tree { ISDP, SDP1, SDP2 };

void print_mas(int *A, int n);
void bubble_sort(int *A, int n);
void obhod_left_to_right(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
vertex *ISPD(int L, int R, int *A);
void SDP_double_cos(int D, vertex *&root);
void SDP_recursion(int D, vertex *&p);
void fill_rand(int *A, int n);
char *get_tree_name(int t);

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int n = 100;
    A = (int *)malloc(n * sizeof(int));
    int size[3];
    int sum[3];
    int height[3];
    int slw[3];
    srand(time(0));
    fill_rand(A, 100);
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, 100);
    printf("\n");
    for (int i = 0; i < 100; i++) {
        SDP_double_cos(A[i], root1);
        SDP_recursion(A[i], root2);
    }
    printf("Обход слеав направо: \n");
    printf("ИСПД: ");
    bubble_sort(A, 100);
    root = ISPD(0, 99, A);
    obhod_left_to_right(root);
    printf("\n\nСДП1: ");
    obhod_left_to_right(root1);
    printf("\n\nСДП2: ");
    obhod_left_to_right(root2);
    printf("\n\n");
    size[0] = size_tree(root);
    sum[0] = sum_tree(root);
    height[0] = height_tree(root);
    slw[0] = sum_len_way(root, 1);
    size[1] = size_tree(root1);
    sum[1] = sum_tree(root1);
    height[1] = height_tree(root1);
    slw[1] = sum_len_way(root1, 1);
    size[2] = size_tree(root2);
    sum[2] = sum_tree(root2);
    height[2] = height_tree(root2);
    slw[2] = sum_len_way(root2, 1);
    printf("|  n=100  | Размер  |  Сумма  |  Высота |Ср.высота|Повтор значения|\n");
    for (int i = 0; i < 3; i++) {
        printf("|%9s|%9d|%9d|%9d|%9.2f|", get_tree_name(i), size[i], sum[i], height[i], slw[i] / (float)size[i]);
        if (duplicate[i] == 0)
            printf("       -       |\n");
        else
            printf("%15d|\n", duplicate[i]);
    }
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
        A[i] = rand() % (80 * n + 1);
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
char *get_tree_name(int t) {
    switch (t) {
        case 0:
            return "ISDP";
        case 1:
            return "SDP1";
        case 2:
            return "SDP2";
    }
}
void SDP_double_cos(int D, vertex *&root) {
    vertex **p = &root;
    while (*p != NULL) {
        if (D < (*p)->data)
            p = &((*p)->left);
        else if (D > (*p)->data)
            p = &((*p)->right);
        else {
            duplicate[1] += 1;
            break;
        }
    }
    if (*p == NULL) {
        *p = new vertex;
        (*p)->data = D;
        (*p)->left = NULL;
        (*p)->right = NULL;
    }
}
void SDP_recursion(int D, vertex *&p) {
    if (p == NULL) {
        p = new (vertex);
        p->data = D;
        p->left = NULL;
        p->right = NULL;
    } else if (D < p->data)
        SDP_recursion(D, p->left);
    else if (D > p->data)
        SDP_recursion(D, p->right);
    else {
        duplicate[2] += 1;
        return;
    }
}
