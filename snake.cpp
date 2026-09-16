#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// ANSI color codes
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define BOLD_GREEN  "\033[1;32m"
#define YELLOW      "\033[33m"
#define CYAN        "\033[36m"

const int WIDTH = 25;
const int HEIGHT = 15;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

struct Point {
    int x, y;
};

Point head;
Point fruit;
std::vector<Point> tail;
int score;
bool gameOver;

void enableRawMode(termios &orig_termios) {
    termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void disableRawMode(const termios &orig_termios) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void setup() {
    gameOver = false;
    dir = STOP;
    head = { WIDTH / 2, HEIGHT / 2 };
    fruit = { rand() % WIDTH, rand() % HEIGHT };
    tail.clear();
    score = 0;
}

void draw() {
    std::cout << "\033[2J\033[H";

    std::cout << CYAN << "=== SNAKE (Wrap-around Mode) ===" << RESET << "\n";

    // Top border
    std::cout << CYAN;
    for (int i = 0; i < WIDTH + 2; ++i) std::cout << "#";
    std::cout << RESET << "\n";

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0) std::cout << CYAN << "#" << RESET;

            if (x == head.x && y == head.y) {
                std::cout << BOLD_GREEN << "O" << RESET; // Snake head
            } else if (x == fruit.x && y == fruit.y) {
                std::cout << RED << "●" << RESET; // Fruit
            } else {
                bool printTail = false;
                for (const auto &segment : tail) {
                    if (segment.x == x && segment.y == y) {
                        std::cout << GREEN << "o" << RESET; // Snake body
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) std::cout << " ";
            }

            if (x == WIDTH - 1) std::cout << CYAN << "#" << RESET;
        }
        std::cout << "\n";
    }

    // Bottom border
    std::cout << CYAN;
    for (int i = 0; i < WIDTH + 2; ++i) std::cout << "#";
    std::cout << RESET << "\n";

    std::cout << YELLOW << "Score: " << score << RESET << " | Press 'q' to quit\n";
}

void input() {
    char c;
    if (read(STDIN_FILENO, &c, 1) > 0) {
        switch (c) {
            case 'a':
            case 'A':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
            case 'D':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
            case 'W':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
            case 'S':
                if (dir != UP) dir = DOWN;
                break;
            case 'q':
            case 'Q':
                gameOver = true;
                break;
        }
    }
}

void logic() {
    if (dir == STOP) return;

    Point prev = head;
    for (size_t i = 0; i < tail.size(); ++i) {
        Point temp = tail[i];
        tail[i] = prev;
        prev = temp;
    }

    switch (dir) {
        case LEFT:  head.x--; break;
        case RIGHT: head.x++; break;
        case UP:    head.y--; break;
        case DOWN:  head.y++; break;
        default: break;
    }

    // Wrap-around screen logic
    if (head.x < 0) head.x = WIDTH - 1;
    else if (head.x >= WIDTH) head.x = 0;

    if (head.y < 0) head.y = HEIGHT - 1;
    else if (head.y >= HEIGHT) head.y = 0;

    // Self-collision
    for (const auto &segment : tail) {
        if (segment.x == head.x && segment.y == head.y) {
            gameOver = true;
            break;
        }
    }

    // Eat fruit
    if (head.x == fruit.x && head.y == fruit.y) {
        score += 10;
        tail.push_back(prev);
        fruit = { rand() % WIDTH, rand() % HEIGHT };
    }
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    termios orig_termios;
    enableRawMode(orig_termios);

    setup();

    while (!gameOver) {
        draw();
        input();
        logic();
        usleep(100000);
    }

    disableRawMode(orig_termios);

    std::cout << "\n" << RED << "Game Over!" << RESET << " Final Score: " << YELLOW << score << RESET << "\n";
    return 0;
}
