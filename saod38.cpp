#include <algorithm>
#include <math.h>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct vertex {
    int data;
    vertex *left;
    vertex *right;
    int weight;
} *root, *root2, *root3;

struct node {
    int data;
    int weight;
};

void add_tree_opt_seek(node D, vertex *&p);
void A1_equally(node *A, int *idx, vertex *&p, int n);
void tree_opt_seek(int L, int R, vertex *&p, node *A, int *idx);
void A2_equally(int L, int R, vertex *&p, node *A, int *idx);
void obhod_left_to_right(vertex *p);
int size_tree(vertex *p);
int total_weight(vertex *p);
double weighted_sum(vertex *p, int level);
double medium_weight_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
void shuffle_array(node *arr, int n);
void fill_rand(node *A, int n);
void weight_rand(node &A);
void print_mas(node *A, int n);
int less(node *A, node *B);
void QuickSort2(int L, int R, int *idx, node *arr);
void bubble_sort(int *idx, node *A, int n);
void AW(int **AW, int n, int *W);
void AP_and_AR(int **AW, int **AR, int **AP, int n);
void tree_opt_seek(int L, int R, int **AR, vertex *&p, node *A, int *idx);
void print_matrix(int **A, int n);

int main(int argc, char const *argv[]) {
    srand(time(0));
    node *A = NULL;
    int n = 6;
    A = (node *)malloc(n * sizeof(node));
    int size;
    int sum;
    int height;
    double med_weight;
    int size2;
    int sum2;
    int height2;
    double med_weight2;
    int size3;
    int sum3;
    int height3;
    double med_weight3;
    srand(time(0));
    fill_rand(A, n);
    int *idx1 = (int *)malloc(n * sizeof(int));
    int *idx2 = (int *)malloc(n * sizeof(int));
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, n);
    printf("\n");
    for (int i = 0; i < n; i++) {
        idx1[i] = i;
        idx2[i] = i;
    }

    QuickSort2(0, n - 1, idx1, A);
    A1_equally(A, idx1, root, n);
    bubble_sort(idx2, A, n);
    int *W = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        W[i] = A[idx2[i]].weight;
    }
    A2_equally(0, n - 1, root2, A, idx2);
    printf("Обход слеав направо: \n");
    obhod_left_to_right(root);
    printf("\n");
    printf("Обход слеав направо: \n");
    obhod_left_to_right(root2);

    int **aw = (int **)malloc((n + 1) * sizeof(int *));
    int **ap = (int **)malloc((n + 1) * sizeof(int *));
    int **ar = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        aw[i] = (int *)calloc((n + 1), sizeof(int));
        ap[i] = (int *)calloc((n + 1), sizeof(int));
        ar[i] = (int *)calloc((n + 1), sizeof(int));
    }
    AW(aw, n, W);
    AP_and_AR(aw, ar, ap, n);
    printf("\nОбход слеав направо: \n");
    obhod_left_to_right(root2);
    printf("\nМатрица AW:\n");
    print_matrix(aw, n);
    printf("\nМатрица AP:\n");
    print_matrix(ap, n);
    printf("\nМатрица AR:\n");
    print_matrix(ar, n);
    tree_opt_seek(0, n, ar, root3, A, idx2);
    size = size_tree(root);
    sum = sum_tree(root);
    height = height_tree(root);
    size2 = size_tree(root2);
    sum2 = sum_tree(root2);
    height2 = height_tree(root2);
    med_weight = medium_weight_tree(root);
    med_weight2 = medium_weight_tree(root2);
    size3 = size_tree(root3);
    sum3 = sum_tree(root3);
    height3 = height_tree(root3);
    med_weight3 = medium_weight_tree(root3);
    double del = (double)ap[0][n] / aw[0][n];
    printf("\n|  Дерево  | Размер  |  Сумма  |  Высота |Ср.взвеш.высота|\n");
    printf("|  ДОП А1  |%9d|%9d|%9d|%15.2f|\n", size, sum, height, med_weight);
    printf("|  ДОП А2  |%9d|%9d|%9d|%15.2f|\n", size2, sum2, height2, med_weight2);
    printf("|  ДОП     |%9d|%9d|%9d|%15.5f|%15.5f", size3, sum3, height3, med_weight3, del);
    return 0;
}

void add_tree_opt_seek(node D, vertex *&p) {
    if (p == NULL) {
        p = new vertex;
        p->data = D.data;
        p->weight = D.weight;
        p->left = NULL;
        p->right = NULL;
    } else if (D.data < p->data)
        add_tree_opt_seek(D, p->left);
    else if (D.data > p->data)
        add_tree_opt_seek(D, p->right);
    else {
        return;
    }
}
void A1_equally(node *A, int *idx, vertex *&p, int n) {
    for (int i = 0; i < n; i++) {
        add_tree_opt_seek(A[idx[i]], p);
    }
}
void A2_equally(int L, int R, vertex *&p, node *A, int *idx) {
    int wes = 0;
    int sum = 0;
    if (L <= R) {
        int i;
        for (i = L; i < R; i++) {
            wes = wes + A[idx[i]].weight;
        }
        for (i = L; i < R; i++) {
            if ((sum < wes / 2) && (sum + A[idx[i]].weight >= wes / 2))
                break;
            sum = sum + A[idx[i]].weight;
        }
        add_tree_opt_seek(A[idx[i]], p);
        A2_equally(L, i - 1, p, A, idx);
        A2_equally(i + 1, R, p, A, idx);
    }
}

void obhod_left_to_right(vertex *p) {
    if (p != NULL) {
        obhod_left_to_right(p->left);
        printf("%d:", p->data + 1);
        printf("%d  ", p->weight);
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
void print_matrix(int **A, int n) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%5d ", A[i][j]);
        }
        printf("\n");
    }
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
int total_weight(vertex *p) {
    if (p == NULL)
        return 0;
    return p->weight + total_weight(p->left) + total_weight(p->right);
}

double weighted_sum(vertex *p, int level) {
    if (p == NULL)
        return 0;
    double current = (double)p->weight * level;
    return current + weighted_sum(p->left, level + 1) + weighted_sum(p->right, level + 1);
}

double medium_weight_tree(vertex *p) {
    if (p == NULL)
        return 0;
    double total_weig = total_weight(p);
    if (total_weig == 0)
        return 0.0;
    double weig_sum = weighted_sum(p, 1);
    return weig_sum / total_weig;
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

void shuffle_array(node *arr, int n) {
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % n;
        std::swap(arr[i], arr[j]);
    }
}

void weight_rand(node &A) { A.weight = 1 + rand() % 100; }

void fill_rand(node *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i].data = i;
        weight_rand(A[i]);
    }
    shuffle_array(A, n);
}

void print_mas(node *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d:", A[i].data);
        printf("%d  ", A[i].weight);
    }
    printf("\n");
}

int less(node *A, node *B) {
    if (A->weight > B->weight)
        return 1;
    else if (A->weight < B->weight)
        return 0;
    else {
        if (A->data > B->data)
            return 1;
        else if (A->data < B->data)
            return 0;
    }
    return 0;
}

void QuickSort2(int L, int R, int *idx, node *arr) {
    while (L < R) {
        int x = idx[L];
        int i = L;
        int j = R;

        while (i <= j) {
            for (; less(&arr[idx[i]], &arr[x]); i++)
                ;
            for (; less(&arr[x], &arr[idx[j]]); j--)
                ;

            if (i <= j) {
                std::swap(idx[i], idx[j]);
                i++;
                j--;
            }
        }

        if (j - L < R - i) {
            if (L < j)
                QuickSort2(L, j, idx, arr);
            L = i;
        } else {
            if (i < R)
                QuickSort2(i, R, idx, arr);
            R = j;
        }
    }
}
void bubble_sort(int *idx, node *A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j--) {
            if (A[idx[j]].data < A[idx[j - 1]].data) {
                std::swap(idx[j], idx[j - 1]);
            }
        }
    }
}

void AW(int **AW, int n, int *W) {
    for (int i = 0; i < n + 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            AW[i][j] = AW[i][j - 1] + W[j - 1];
        }
    }
}
void AP_and_AR(int **AW, int **AR, int **AP, int n) {
    int min, m, x, j;
    for (int i = 0; i < n; i++) {
        j = i + 1;
        AP[i][j] = AW[i][j];
        AR[i][j] = j;
    }
    for (int h = 2; h <= n; h++) {
        for (int i = 0; i <= n - h; i++) {
            j = i + h;
            m = AR[i][j - 1];
            min = AP[i][m - 1] + AP[m][j];
            for (int k = m + 1; k <= AR[i + 1][j]; k++) {
                x = AP[i][k - 1] + AP[k][j];
                if (x < min) {
                    m = k;
                    min = x;
                }
            }
            AP[i][j] = min + AW[i][j];
            AR[i][j] = m;
        }
    }
}

void tree_opt_seek(int L, int R, int **AR, vertex *&p, node *A, int *idx) {
    if (L < R) {
        int k = AR[L][R];
        add_tree_opt_seek(A[idx[k - 1]], p);
        tree_opt_seek(L, k - 1, AR, p, A, idx);
        tree_opt_seek(k, R, AR, p, A, idx);
    }
}