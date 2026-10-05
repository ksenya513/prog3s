#include <SFML/Graphics.hpp>
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
void obhod_top_to_bottom(vertex *p);
void SDP_double_cos(int D, vertex *&root);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
vertex *ISPD(int L, int R, int *A);
void turn_RL(vertex *&p);
void turn_LR(vertex *&p);
void turn_RR(vertex *&p);
void turn_LL(vertex *&p);
void AVL_tree(int D, vertex *&root);
void fill_rand(int *A, int n);
bool rost;

void draw_tree_top_down(sf::RenderWindow &window, vertex *p, float x, float y, float x_lenght, const sf::Font &font) {
    if (p == NULL)
        return;

    float y_step = 70.0f;
    float radius = 15.0f;
    if (p->left != NULL) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght, y + y_step), sf::Color(255, 150, 0))};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    } else {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght - 5, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght + 5, y + y_step), sf::Color(255, 150, 0))};
        window.draw(line, 4, sf::PrimitiveType::Lines);
    }
    if (p->right != NULL) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght, y + y_step), sf::Color(255, 150, 0))};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    } else {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght - 5, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght + 5, y + y_step), sf::Color(255, 150, 0))};
        window.draw(line, 4, sf::PrimitiveType::Lines);
    }
    draw_tree_top_down(window, p->left, x - x_lenght, y + y_step, x_lenght / 2, font);
    draw_tree_top_down(window, p->right, x + x_lenght, y + y_step, x_lenght / 2, font);
    sf::CircleShape krug(radius);
    krug.setFillColor(sf::Color(200, 150, 90));
    krug.setOutlineThickness(2.0f);
    krug.setOutlineColor(sf::Color(160, 110, 50));
    krug.setPosition(sf::Vector2f(x - 7, y));
    sf::Text text(font, std::to_string(p->data), 12);
    text.setFillColor(sf::Color::White); // 50, 34, 26
    text.setPosition(sf::Vector2f(x - 2, y + 5));
    window.draw(krug);
    window.draw(text);
}

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int n = 100;
    A = (int *)malloc(n * sizeof(int));
    srand(time(0));
    fill_rand(A, 100);
    print_mas(A, 100);
    for (int i = 0; i < 100; i++) {
        AVL_tree(A[i], root);
    }
    printf("\n\n\n");
    obhod_left_to_right(root);
    sf::RenderWindow window(sf::VideoMode({1950, 1000}), "Derevo");
    window.setFramerateLimit(60);
    sf::Font font;
    font.openFromFile("C:\\Windows\\Fonts\\arial.ttf");
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color(219, 215, 210));
        if (root != NULL) {
            draw_tree_top_down(window, root, 950.0f, 50.0f, 480.0f, font);
        }
        window.display();
    }
    return 0;
}

void obhod_top_to_bottom(vertex *p) {
    if (p != NULL) {
        printf(" %d ", p->data);
        obhod_top_to_bottom(p->left);
        obhod_top_to_bottom(p->right);
    } else {
        printf("_ ");
    }
}

void obhod_left_to_right(vertex *p) {
    if (p != nullptr) {
        obhod_left_to_right(p->left);
        printf("%d ", p->data);
        obhod_left_to_right(p->right);
    }
}
vertex *ISPD(int L, int R, int *A) {
    if (L > R)
        return nullptr;
    else {
        int m = (L + R) / 2;
        vertex *p = (vertex *)malloc(sizeof(vertex));
        p->data = A[m];
        p->left = ISPD(L, m - 1, A);
        p->right = ISPD(m + 1, R, A);
        return p;
    }
}

void fill_rand(int *A, int n) {
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
void SDP_double_cos(int D, vertex *&root) {
    vertex **p = &root;
    while (*p != NULL) {
        if (D < (*p)->data)
            p = &((*p)->left);
        else if (D > (*p)->data)
            p = &((*p)->right);
        else {
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
// g++ grafic.cpp -lsfml-graphics -lsfml-window -lsfml-system -o fzar.exe