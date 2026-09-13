#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

struct vertex {
    int data;
    vertex *left;
    vertex *right;
} *root;

// Прототипы функций
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

// Графическая отрисовка дерева под SFML 3 (Top-to-Bottom / Pre-order)
void draw_tree_top_down(sf::RenderWindow &window, vertex *p, float x, float y, float x_offset, const sf::Font &font) {
    if (p == nullptr)
        return;

    float y_step = 60.0f; // Шаг по вертикали
    float radius = 18.0f; // Радиус узла

    // 1. Отрисовка линий к дочерним узлам (sf::PrimitiveType::Lines в SFML 3)
    if (p->left != nullptr) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color::Black), sf::Vertex(sf::Vector2f(x - x_offset, y + y_step), sf::Color::Black)};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    if (p->right != nullptr) {
        sf::Vertex line[] = {sf::Vertex(sf::Vector2f(x, y), sf::Color::Black), sf::Vertex(sf::Vector2f(x + x_offset, y + y_step), sf::Color::Black)};
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // 2. Отрисовка круга (узла)
    sf::CircleShape node(radius);
    node.setFillColor(sf::Color(200, 150, 90));
    node.setOutlineThickness(2.0f);
    node.setOutlineColor(sf::Color::Black);
    node.setOrigin(sf::Vector2f(radius, radius));
    node.setPosition(sf::Vector2f(x, y));

    // 3. Отрисовка текста
    sf::Text text(font, std::to_string(p->data), 14);
    text.setFillColor(sf::Color::Black);

    // В SFML 3 у Rect вместо left/top/width/height используются position (x, y) и size (x, y)
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f));
    text.setPosition(sf::Vector2f(x, y));

    window.draw(node);
    window.draw(text);

    // 4. Рекурсивный переход к левому и правому поддеревьям
    draw_tree_top_down(window, p->left, x - x_offset, y + y_step, x_offset / 2.0f, font);
    draw_tree_top_down(window, p->right, x + x_offset, y + y_step, x_offset / 2.0f, font);
}

int main(int argc, char const *argv[]) {
    int n = 31; // 31 узел — идеально для 5 уровней дерева
    int *A = (int *)malloc(n * sizeof(int));

    srand((unsigned int)time(0));
    fill_rand(A, n);

    printf("\nИсходный массив: ");
    print_mas(A, n);
    printf("\n");

    bubble_sort(A, n);
    printf("Отсортированный массив: ");
    print_mas(A, n);
    printf("\n");

    root = ISPD(0, n - 1, A);

    printf("Обход слева направо: ");
    obhod_left_to_right(root);
    printf("\n");

    printf("Обход сверху вниз: ");
    obhod_top_to_bottom(root);
    printf("\n\n");

    int size = size_tree(root);
    int sum = sum_tree(root);
    int height = height_tree(root);
    int slw = sum_len_way(root, 1);

    printf("| Размер  |  Сумма  |  Высота |Ср.высота|\n");
    printf("|%9d|%9d|%9d|%9.2f|\n", size, sum, height, slw / (float)size);

    // Инициализация окна в SFML 3
    sf::RenderWindow window(sf::VideoMode({1200, 700}), "ISPD Tree Visualization (SFML 3)");
    window.setFramerateLimit(60);

    // В SFML 3 шрифты загружаются через openFromFile
    sf::Font font;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        printf("Ошибка: не удалось загрузить шрифт C:\\Windows\\Fonts\\arial.ttf\n");
    }

    // Текстовые метки
    sf::Text xLabel(font, "n", 20);
    xLabel.setFillColor(sf::Color::Red);
    xLabel.setPosition(sf::Vector2f(1150.0f, 650.0f));

    sf::Text yLabel(font, "C+M", 20);
    yLabel.setFillColor(sf::Color::Red);
    yLabel.setPosition(sf::Vector2f(25.0f, 25.0f));

    // Цикл событий SFML 3
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        if (root != nullptr) {
            draw_tree_top_down(window, root, 600.0f, 50.0f, 280.0f, font);
        }

        window.draw(xLabel);
        window.draw(yLabel);

        window.display();
    }

    free(A);
    return 0;
}

// Консольный обход сверху вниз
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

int size_tree(vertex *p) { return (p == nullptr) ? 0 : 1 + size_tree(p->left) + size_tree(p->right); }

int sum_tree(vertex *p) { return (p == nullptr) ? 0 : p->data + sum_tree(p->left) + sum_tree(p->right); }

int height_tree(vertex *p) { return (p == nullptr) ? 0 : 1 + std::max(height_tree(p->left), height_tree(p->right)); }

int sum_len_way(vertex *p, int l) { return (p == nullptr) ? 0 : l + sum_len_way(p->left, l + 1) + sum_len_way(p->right, l + 1); }

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