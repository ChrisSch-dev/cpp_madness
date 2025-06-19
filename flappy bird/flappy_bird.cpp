#include <iostream>
#include <conio.h>   // For _kbhit() and _getch()
#include <windows.h> // For Sleep()
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int width = 40;
const int height = 20;
const int pipeGap = 6;
const int pipeDist = 18;

struct Pipe {
    int x;
    int gapY;
};

void setup();
void draw();
void input();
void logic();

int birdY, score, frames, velocity;
bool gameOver;
vector<Pipe> pipes;

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(50); // ~20 FPS
    }
    cout << "\nGame Over! Final Score: " << score << endl;
    system("pause");
    return 0;
}

void setup() {
    srand(time(0));
    birdY = height / 2;
    score = 0;
    frames = 0;
    velocity = 0;
    gameOver = false;
    pipes.clear();
    pipes.push_back({width - 1, rand() % (height - pipeGap - 2) + 1});
}

void draw() {
    system("cls");
    // Draw top border
    for (int i = 0; i < width + 2; ++i) cout << "#";
    cout << endl;

    for (int y = 0; y < height; ++y) {
        cout << "#";
        for (int x = 0; x < width; ++x) {
            bool printed = false;

            // Draw bird
            if (x == 5 && y == birdY) {
                cout << "O";
                printed = true;
            }

            // Draw pipes
            for (const Pipe& p : pipes) {
                if (x == p.x && (y < p.gapY || y > p.gapY + pipeGap)) {
                    cout << "|";
                    printed = true;
                }
            }

            if (!printed) cout << " ";
        }
        cout << "#" << endl;
    }
    // Draw bottom border
    for (int i = 0; i < width + 2; ++i) cout << "#";
    cout << "\nScore: " << score << endl;
}

void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == ' ' || ch == 'w')
            velocity = -3; // Flap
        else if (ch == 'q')
            gameOver = true;
    }
}

void logic() {
    frames++;
    velocity += 1; // Gravity
    if (velocity > 2) velocity = 2;
    birdY += velocity;
    if (birdY < 0) birdY = 0;
    if (birdY >= height) {
        gameOver = true;
        return;
    }

    // Move pipes
    for (Pipe& p : pipes)
        p.x--;

    // Add new pipe
    if (pipes.back().x == width - pipeDist) {
        pipes.push_back({width - 1, rand() % (height - pipeGap - 2) + 1});
    }

    // Remove passed pipes and score
    if (!pipes.empty() && pipes.front().x < 0) {
        pipes.erase(pipes.begin());
        score++;
    }

    // Collision detection
    for (const Pipe& p : pipes) {
        if (p.x == 5) {
            if (birdY < p.gapY || birdY > p.gapY + pipeGap) {
                gameOver = true;
            }
        }
    }
}