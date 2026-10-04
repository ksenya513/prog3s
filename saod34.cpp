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
} *root;

void print_mas(int *A, int n);
void obhod_left_to_right(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
void SDP_recursion(int D, vertex *&p);
void fill_rand(int *A, int n);
char *get_tree_name(int t);
void delete_SDP(int D, vertex *&root);

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
    int w = 0;
    int n = 20;
    A = (int *)malloc(n * sizeof(int));
    int size;
    int sum;
    int height;
    int slw;
    srand(time(0));
    fill_rand(A, 20);
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, 20);
    printf("\n");
    for (int i = 0; i < 20; i++) {
        SDP_recursion(A[i], root);
    }
    printf("обход слева направо: \n");
    obhod_left_to_right(root);
    printf("\n\n");
    sf::RenderWindow window(sf::VideoMode({1800, 750}), "Derevo");
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
            draw_tree_top_down(window, root, 700.0f, 50.0f, 350.0f, font);
        }
        window.display();
        if (w < 10) {
            int t;
            printf("Введите вершину, которую необходимо удалить\n");
            scanf("%d", &t);
            delete_SDP(t, root);
            w++;
        }
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

void fill_rand(int *A, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
    }
}
void print_mas(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
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
        return;
    }
}
void delete_SDP(int D, vertex *&root) {
    vertex **p = &root;
    vertex *q;
    vertex *r;
    vertex *s;
    while (*p != NULL) {
        if (D < (*p)->data) {
            p = &((*p)->left);
        } else if (D > (*p)->data) {
            p = &((*p)->right);
        } else {
            break;
        }
    }
    if (*p != NULL) {
        q = *p;
        if (q->left == NULL) {
            *p = q->right;
        } else if (q->right == NULL) {
            *p = q->left;
        } else {
            r = q->left;
            s = q;
            if (r->right == NULL) {
                r->right = q->right;
            } else {
                while (r->right != NULL) {
                    s = r;
                    r = r->right;
                }
                s->right = r->left;
                r->left = q->left;
                r->right = q->right;
                *p = r;
            }
        }
    }
    delete (q);
}
// g++ saod34.cpp -lsfml-graphics -lsfml-window -lsfml-system -o fzar.exe