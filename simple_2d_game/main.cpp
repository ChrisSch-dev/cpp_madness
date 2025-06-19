#include <iostream>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <conio.h> // For Linux, use ncurses or edit for portable input
#include <fstream>

struct Coord { int x, y; };
enum Direction { UP, DOWN, LEFT, RIGHT };

int width = 20, height = 10, score = 0;
bool gameOver = false, paused = false;
Coord fruit, head;
std::deque<Coord> tail;
Direction dir = RIGHT;

void draw() {
    system("cls"); // "clear" for Linux
    for (int i = 0; i < width+2; i++) std::cout << "#";
    std::cout << "\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0) std::cout << "#";
            if (x == head.x && y == head.y) std::cout << "O";
            else if (x == fruit.x && y == fruit.y) std::cout << "F";
            else {
                bool printTail = false;
                for (const auto& t : tail) if (t.x == x && t.y == y) printTail = true;
                std::cout << (printTail ? "o" : " ");
            }
            if (x == width-1) std::cout << "#";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < width+2; i++) std::cout << "#";
    std::cout << "\nScore: " << score << std::endl;
    std::cout << "Press P to pause/resume, Q to quit.\n";
}

void input() {
    if (_kbhit()) {
        char c = _getch();
        if (c == 'w' && dir != DOWN) dir = UP;
        if (c == 's' && dir != UP) dir = DOWN;
        if (c == 'a' && dir != RIGHT) dir = LEFT;
        if (c == 'd' && dir != LEFT) dir = RIGHT;
        if (c == 'p' || c == 'P') paused = !paused;
        if (c == 'q' || c == 'Q') gameOver = true;
    }
}

void logic() {
    if (paused) return;
    Coord prev = head;
    switch (dir) {
        case UP: head.y--; break;
        case DOWN: head.y++; break;
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
    }
    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)
        gameOver = true;
    tail.push_front(prev);
    if (head.x == fruit.x && head.y == fruit.y) {
        score++;
        fruit.x = rand()%width; fruit.y = rand()%height;
    } else {
        tail.pop_back();
    }
    for (const auto& t : tail)
        if (t.x == head.x && t.y == head.y)
            gameOver = true;
}

void save_score() {
    std::ofstream ofs("scores.txt", std::ios::app);
    ofs << score << "\n";
    ofs.close();
}

void show_high_scores() {
    std::ifstream ifs("scores.txt");
    std::vector<int> scores;
    int s;
    while (ifs >> s) scores.push_back(s);
    std::sort(scores.rbegin(), scores.rend());
    std::cout << "High Scores:\n";
    for (int i = 0; i < std::min(5, (int)scores.size()); ++i)
        std::cout << scores[i] << std::endl;
}

int main() {
    srand(time(0));
    head = {width/2, height/2};
    fruit = {rand()%width, rand()%height};
    std::cout << "Snake Game!\n";
    show_high_scores();
    while (!gameOver) {
        draw();
        input();
        logic();
        std::this_thread::sleep_for(std::chrono::milliseconds(115));
    }
    std::cout << "Game Over! Final Score: " << score << "\n";
    save_score();
}