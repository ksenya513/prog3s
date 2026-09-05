#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct vertex{
    int data;
    vertex *left;
    vertex *right;
}*root;

void obhod_top_to_bottom(vertex *p);
void obhod_left_to_right(vertex *p);
void obhod_bottom_to_top(vertex *p);

int main(int argc, char const *argv[]){
    srand(time(0));

    root = (vertex*)malloc(sizeof(vertex));
    root->data = rand() % 20 + 1;
    root->right = NULL;

    root->left = (vertex*)malloc(sizeof(vertex));
    root->left->data = rand() % 20 + 1;

    root->left->right = (vertex*)malloc(sizeof(vertex));
    root->left->right->data = rand() % 20 + 1;
    root->left->right->left = NULL;
    root->left->right->right = NULL;

    root->left->left = (vertex*)malloc(sizeof(vertex));
    root->left->left->data = rand() % 20 + 1;
    root->left->left->left = NULL;

    root->left->left->right = (vertex*)malloc(sizeof(vertex));
    root->left->left->right->data = rand() % 20 + 1;
    root->left->left->right->right = NULL;

    root->left->left->right->left = (vertex*)malloc(sizeof(vertex));
    root->left->left->right->left->data = rand() % 20 + 1;
    
    root->left->left->right->left->left = NULL; 
    root->left->left->right->left->right = NULL;
    printf("Обход сверху вниз: ");
    obhod_top_to_bottom(root);
    printf("\n");
    printf("Обход слева направо: ");
    obhod_left_to_right(root);
    printf("\n");
    printf("Обход снизу вверх: ");
    obhod_bottom_to_top(root);
    printf("\n");
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