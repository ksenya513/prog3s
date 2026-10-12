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
void del_left(vertex *&p);
void del_right(vertex *&p);
void turn_RR1(vertex *&p);
void turn_LL1(vertex *&p);
void delete_AVL(int D, vertex *&root);

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
bool ymensh;
bool rost;

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int w = 0;
    int n = 20;
    A = (int *)malloc(n * sizeof(int));
    srand(time(0));
    fill_rand(A, 20);
    printf("\n");
    printf("Исходный массив: ");
    print_mas(A, 20);
    printf("\n");
    for (int i = 0; i < 20; i++) {
        AVL_tree(A[i], root);
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
            printf("Введите вершину, которую необходимо удалить (можно удалить %d)\n", (10 - w));
            scanf("%d", &t);
            delete_AVL(t, root);
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

void del_left(vertex *&p) {
    if (p->balance == -1) {
        p->balance = 0;
    } else if (p->balance == 0) {
        p->balance = 1;
        ymensh = false;
    } else if (p->balance == 1) {
        if (p->right->balance >= 0) {
            turn_RR1(p);
        } else {
            turn_RL(p);
        }
    }
}

void del_right(vertex *&p) {
    if (p->balance == 1) {
        p->balance = 0;
    } else if (p->balance == 0) {
        p->balance = -1;
        ymensh = false;
    } else if (p->balance == -1) {
        if (p->left->balance <= 0) {
            turn_LL1(p);
        } else {
            turn_LR(p);
        }
    }
}

void turn_RR1(vertex *&p) {
    vertex *q = p->left;
    if (q->balance == 0) {
        q->balance = -1;
        p->balance = 1;
        ymensh = false;
    } else {
        q->balance = 0;
        p->balance = 0;
    }
    p->right = q->left;
    q->left = p;
    p = q;
}
void turn_LL1(vertex *&p) {
    vertex *q = p->left;
    if (q->balance == 0) {
        q->balance = 1;
        p->balance = -1;
        ymensh = false;
    } else {
        q->balance = 0;
        p->balance = 0;
    }
    p->left = q->right;
    q->right = p;
    p = q;
}
void del(vertex *&r, vertex *&q) {
    if (r->right != NULL) {
        del(r->right, q);
        if (ymensh == true)
            del_right(r);
    } else {
        q->data = r->data;
        q = r;
        r = r->left;
        ymensh = true;
    }
}
void delete_AVL(int D, vertex *&p) {
    vertex *q = NULL;
    if (p == NULL)
        return;
    else if (D < p->data) {
        delete_AVL(D, p->left);
        if (ymensh == true)
            del_left(p);
    } else if (D > p->data) {
        delete_AVL(D, p->right);
        if (ymensh == true)
            del_right(p);
    } else {
        q = p;
        if (q->left == NULL) {
            p = q->right;
            ymensh = true;
        } else if (q->right == NULL) {
            p = q->left;
            ymensh = true;
        } else {
            del(q->left, q);
            if (ymensh == true)
                del_left(p);
        }
    }
    free(q);
}

// g++ saod36.cpp -lsfml-graphics -lsfml-window -lsfml-system -o fzar.exe