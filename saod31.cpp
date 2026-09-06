#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

struct vertex{
    int data;
    vertex *left;
    vertex *right;
}*root;

void obhod_top_to_bottom(vertex *p);
void obhod_left_to_right(vertex *p);
void obhod_bottom_to_top(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p,int l);

int main(int argc, char const *argv[]){
    srand(time(0));

    root=(vertex*)malloc(sizeof(vertex));
    root->data=rand() % 20 + 1;
    root->right=NULL;

    root->left=(vertex*)malloc(sizeof(vertex));
    root->left->data=rand() % 20 + 1;

    root->left->right=(vertex*)malloc(sizeof(vertex));
    root->left->right->data=rand() % 20 + 1;
    root->left->right->left=NULL;
    root->left->right->right=NULL;

    root->left->left=(vertex*)malloc(sizeof(vertex));
    root->left->left->data=rand() % 20 + 1;
    root->left->left->left=NULL;

    root->left->left->right=(vertex*)malloc(sizeof(vertex));
    root->left->left->right->data=rand() % 20 + 1;
    root->left->left->right->right=NULL;

    root->left->left->right->left=(vertex*)malloc(sizeof(vertex));
    root->left->left->right->left->data=rand() % 20 + 1;
    
    root->left->left->right->left->left=NULL; 
    root->left->left->right->left->right=NULL;
    printf("Обход сверху вниз: ");
    obhod_top_to_bottom(root);
    printf("\n");
    printf("Обход слеав направо: ");
    obhod_left_to_right(root);
    printf("\n");
    printf("Обход снизу вверх: ");
    obhod_bottom_to_top(root);
    printf("\n\n");
    int size=size_tree(root);
    int sum=sum_tree(root);
    int height=height_tree(root);
    int slw=sum_len_way(root,1);
    printf("| Размер  |  Сумма  |  Высота |Ср.высота|\n");
    printf("|%9d|%9d|%9d|%9.2f|",size,sum,height,slw/(float)size);
    return 0;
}

void obhod_top_to_bottom(vertex *p){
    if(p!=NULL){
        printf(" %d ",p->data);
        obhod_top_to_bottom(p->left);
        obhod_top_to_bottom(p->right);
    }else printf("_ ");
}
void obhod_left_to_right(vertex *p){
    if(p!=NULL){
        obhod_left_to_right(p->left);
        printf(" %d ",p->data);
        obhod_left_to_right(p->right);
    }else printf("_ ");
}
void obhod_bottom_to_top(vertex *p){
    if(p!=NULL){
        obhod_bottom_to_top(p->left);
        obhod_bottom_to_top(p->right);
        printf(" %d ",p->data);
    }else printf("_ ");
}

int size_tree(vertex *p){
    int n;
    if(p==NULL){
        n=0;
    }else{
        n=1+size_tree(p->left)+size_tree(p->right);
    }
    return n;
}
int sum_tree(vertex *p){
    int s;
    if(p==NULL){
        s=0;
    }else{
        s=p->data+sum_tree(p->left)+sum_tree(p->right);
    }
    return s;
}
int height_tree(vertex *p){
    int h;
    if(p==NULL){
        h=0;
    }else{
        h=1+std::max(height_tree(p->left),height_tree(p->right));
    }
    return h;
}
int sum_len_way(vertex *p,int l){
    int s;
    if(p==NULL){
        s=0;
    }else{
        s=l+sum_len_way(p->left,l+1)+sum_len_way(p->right,l+1);
    }
    return s;
}