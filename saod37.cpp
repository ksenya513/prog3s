#include <SFML/Graphics.hpp>
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
    int balance;
} *root, *root2, *root3;
bool vert_r;
bool hor_r;
bool rost;

void print_mas(int *A, int n);
void obhod_left_to_right(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
void fill_rand(int *A, int n);
void dbd_tree(int D, vertex *&p);
void turn_RL(vertex *&p);
void turn_LR(vertex *&p);
void turn_RR(vertex *&p);
void turn_LL(vertex *&p);
void AVL_tree(int D, vertex *&root);
void shuffle_array(int arr, int n);
void draw_dbd_tree(sf::RenderWindow &window, vertex *p, float x, float y, float x_lenght, const sf::Font &font) {
    if (p == NULL)
        return;

    float y_step = 60.0f;
    float radius = 15.0f;

    if (p->left != NULL) {
        bool horizontal = (p->left->balance == 1);

        float target_y;
        if (horizontal) {
            target_y = y;
        } else {
            target_y = y + y_step;
        }

        float target_x = x - x_lenght;

        sf::Color line_color;
        if (horizontal) {
            line_color = sf::Color(150, 170, 100);
        } else {
            line_color = sf::Color(255, 150, 0);
        }

        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), line_color), sf::Vertex(sf::Vector2f(target_x, target_y), line_color)};
        window.draw(line, 2, sf::PrimitiveType::Lines);

        draw_dbd_tree(window, p->left, target_x, target_y, x_lenght / 2, font);
    } else {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght - 5, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x - x_lenght + 5, y + y_step), sf::Color(255, 150, 0))};
        window.draw(line, 4, sf::PrimitiveType::Lines);
    }

    if (p->right != NULL) {
        bool horizontal = (p->right->balance == 1);

        float target_y;
        if (horizontal) {
            target_y = y;
        } else {
            target_y = y + y_step;
        }

        float target_x = x + x_lenght;

        sf::Color line_color;
        if (horizontal) {
            line_color = sf::Color(50, 170, 100);
        } else {
            line_color = sf::Color(255, 150, 0);
        }

        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), line_color), sf::Vertex(sf::Vector2f(target_x, target_y), line_color)};
        window.draw(line, 2, sf::PrimitiveType::Lines);

        draw_dbd_tree(window, p->right, target_x, target_y, x_lenght / 2, font);
    } else {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght - 5, y + y_step), sf::Color(255, 150, 0)),
                             sf::Vertex(sf::Vector2f(x + x_lenght + 5, y + y_step), sf::Color(255, 150, 0))};
        window.draw(line, 4, sf::PrimitiveType::Lines);
    }

    sf::CircleShape krug(radius);
    krug.setFillColor(sf::Color(200, 150, 90));
    krug.setOutlineThickness(2.0f);
    krug.setOutlineColor(sf::Color(160, 110, 50));
    krug.setPosition(sf::Vector2f(x - 7, y));

    sf::Text text(font, std::to_string(p->data), 12);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(x - 2, y + 5));

    window.draw(krug);
    window.draw(text);
}

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int n = 100;
    A = (int *)malloc(n * sizeof(int));
    int size;
    int sum;
    int height;
    int slw;
    int size2;
    int sum2;
    int height2;
    int slw2;
    srand(time(0));
    fill_rand(A, 100);
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, 100);
    printf("\n");
    for (int i = 0; i < 100; i++) {
        AVL_tree(A[i], root);
    }
    for (int i = 0; i < 100; i++) {
        dbd_tree(A[i], root2);
    }
    printf("Обход слеав направо: \n");
    obhod_left_to_right(root2);
    size = size_tree(root);
    sum = sum_tree(root);
    height = height_tree(root);
    slw = sum_len_way(root, 1);
    size2 = size_tree(root2);
    sum2 = sum_tree(root2);
    height2 = height_tree(root2);
    slw2 = sum_len_way(root2, 1);
    printf("\n|  Дерево  | Размер  |  Сумма  |  Высота |Ср.высота|\n");
    printf("|АВЛ-дерево|%9d|%9d|%9d|%9.2f|\n", size, sum, height, slw / (float)size);
    printf("|ДБД-дерево|%9d|%9d|%9d|%9.2f|", size2, sum2, height2, slw2 / (float)size2);
    int draw_n = 100;
    for (int i = 0; i < draw_n; i++) {
        dbd_tree(A[i], root3);
    }
    sf::RenderWindow window(sf::VideoMode({5500, 750}), "dbd tree");
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
        if (root3 != NULL) {
            draw_dbd_tree(window, root3, 2600.0f, 20.0f, 1350.0f, font);
        }
        window.display();
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

void shuffle_array(int *arr, int n) {
    srand(time(0));
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % n;
        std::swap(arr[i], arr[j]);
    }
}

void fill_rand(int *A, int n) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
    shuffle_array(A, n);
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
void dbd_tree(int D, vertex *&p) {
    if (p == NULL) {
        p = new vertex;
        p->data = D;
        p->left = p->right = NULL;
        p->balance = 0;
        vert_r = true;
    } else if (p->data > D) {
        dbd_tree(D, p->left);
        if (vert_r == true) {
            if (p->balance == 0) {
                vertex *q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->balance = 1;
                vert_r = false;
                hor_r = true;
            } else {
                p->balance = 0;
                vert_r = true;
                hor_r = false;
            }
        } else
            hor_r = false;
    } else if (p->data < D) {
        dbd_tree(D, p->right);
        if (vert_r == true) {
            p->balance = 1;
            hor_r = true;
            vert_r = false;
        } else if (hor_r == true) {
            if (p->balance == 1) {
                vertex *q = p->right;
                p->balance = 0;
                q->balance = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                vert_r = 1;
                hor_r = 0;
            } else
                hor_r = 0;
        }
    }
}
// g++ saod37.cpp -lsfml-graphics -lsfml-window -lsfml-system -o fzar.exe