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
    int balance;
} *root;

void print_mas(int *A, int n);
void obhod_left_to_right(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
void fill_rand(int *A, int n);
void turn_RL(vertex *&p);
void turn_LR(vertex *&p);
void turn_RR(vertex *&p);
void turn_LL(vertex *&p);
void AVL_tree(int D, vertex *&root);

bool rost;

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int n = 100;
    A = (int *)malloc(n * sizeof(int));
    int size;
    int sum;
    int height;
    int slw;
    srand(time(0));
    fill_rand(A, 100);
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, 100);
    printf("\n");
    for (int i = 0; i < 100; i++) {
        AVL_tree(A[i], root);
    }
    printf("Обход слеав направо: \n");
    obhod_left_to_right(root);
    size = size_tree(root);
    sum = sum_tree(root);
    height = height_tree(root);
    slw = sum_len_way(root, 1);
    printf("\n| Размер  |  Сумма  |  Высота |Ср.высота|\n");
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
void turn_LL(vertex *&p) {
    vertex *q = p->left;
    p->balance = 0;
    q->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}
void turn_RR(vertex *&p) {
    vertex *q = p->right;
    p->balance = 0;
    q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}
void turn_LR(vertex *&p) {
    vertex *q = p->left;
    vertex *r = q->right;
    if (r->balance < 0)
        p->balance = 1;
    else
        p->balance = 0;

    if (r->balance > 0)
        q->balance = -1;
    else
        q->balance = 0;

    r->balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}
void turn_RL(vertex *&p) {
    vertex *q = p->right;
    vertex *r = q->left;
    if (r->balance > 0)
        p->balance = -1;
    else
        p->balance = 0;

    if (r->balance < 0)
        q->balance = 1;
    else
        q->balance = 0;

    r->balance = 0;
    q->left = r->right;
    p->right = r->left;
    r->left = p;
    r->right = q;
    p = r;
}
void AVL_tree(int D, vertex *&p) {
    if (p == NULL) {
        p = new vertex;
        p->data = D;
        p->left = p->right = NULL;
        p->balance = 0;
        rost = true;
    } else if (p->data > D) {
        AVL_tree(D, p->left);
        if (rost == true) { // выросав левая ветвь
            if (p->balance > 0) {
                p->balance = 0;
                rost = false;
            } else if (p->balance == 0) {
                p->balance = -1;
                rost = true;
            } else if (p->left->balance < 0) {
                turn_LL(p);
                rost = false;
            } else {
                turn_LR(p);
                rost = false;
            }
        }
    } else if (p->data < D) {
        AVL_tree(D, p->right);
        if (rost == true) { // выросла правая ветвь
            if (p->balance < 0) {
                p->balance = 0;
                rost = false;
            } else if (p->balance == 0) {
                p->balance = 1;
                rost = true;
            } else if (p->right->balance > 0) {
                turn_RR(p);
                rost = false;
            } else {
                turn_RL(p);
                rost = false;
            }
        }
    } else {
        rost = false;
    }
}
