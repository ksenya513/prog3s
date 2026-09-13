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
void bubble_sort(int *A, int n);
void obhod_left_to_right(vertex *p);
void obhod_top_to_bottom(vertex *p);
int size_tree(vertex *p);
int sum_tree(vertex *p);
int height_tree(vertex *p);
int sum_len_way(vertex *p, int l);
vertex *ISPD(int L, int R, int *A);
void fill_rand(int *A, int n);

void draw_tree_top_down(sf::RenderWindow &window, vertex *p, float x, float y, float x_lenght, const sf::Font &font) {
    if (p == NULL)
        return;

    float y_step = 75.0f; // Шаг по вертикали
    float radius = 15.0f; // Радиус узла
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
    draw_tree_top_down(window, p->left, x - x_lenght, y + y_step, x_lenght / 2, font);
    draw_tree_top_down(window, p->right, x + x_lenght, y + y_step, x_lenght / 2, font);
}

int main(int argc, char const *argv[]) {
    int *A = NULL;
    int n = 100;
    A = (int *)malloc(n * sizeof(int));
    srand(time(0));
    fill_rand(A, 100);
    bubble_sort(A, n);
    root = ISPD(0, 99, A);
    sf::RenderWindow window(sf::VideoMode({1950, 720}), "Derevo");
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
        if (root != nullptr) {
            // центр(600,50) и сдвигом 400
            draw_tree_top_down(window, root, 950.0f, 50.0f, 480.0f, font);
        }
        window.display();
    }
    return 0;
}

void obhod_top_to_bottom(vertex *p) {
    if (p != nullptr) {
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
// g++ grafic.cpp -lsfml-graphics -lsfml-window -lsfml-system -o fzar.exe