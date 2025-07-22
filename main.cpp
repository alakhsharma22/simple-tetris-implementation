#include "terminal.h"
#include "tetris.h"
#include "renderer.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

int main() {
    enableRawMode();
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<int> field(FIELD_WIDTH * FIELD_HEIGHT, 0);
    int currentPiece = std::rand() % 7;
    int nextPiece    = std::rand() % 7;
    int rotation     = 0;
    int posX         = FIELD_WIDTH / 2 - 2;
    int posY         = 0;
    bool gameOver    = false;

    const float dropDelay = 0.5f;
    float timer = 0.0f;
    auto lastTime = std::chrono::steady_clock::now();

    while (!gameOver) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - lastTime;
        lastTime = now;
        timer += elapsed.count();
        
        if (kbhit()) {
            char c;
            read(STDIN_FILENO, &c, 1);
            if (c == 'q') break;
            if (c == '\x1B') {
                char seq[2];
                if (read(STDIN_FILENO, &seq[0], 1) && read(STDIN_FILENO, &seq[1], 1) && seq[0] == '[') {
                    if (seq[1] == 'D' && doesFit(field, currentPiece, rotation, posX-1, posY))
                        posX--;
                    if (seq[1] == 'C' && doesFit(field, currentPiece, rotation, posX+1, posY))
                        posX++;
                    if (seq[1] == 'B' && doesFit(field, currentPiece, rotation, posX, posY+1))
                        posY++;
                    if (seq[1] == 'A' && doesFit(field, currentPiece, rotation+1, posX, posY))
                        rotation++;
                }
            }
        }
        
        if (timer > dropDelay) {
            if (doesFit(field, currentPiece, rotation, posX, posY+1)) {
                posY++;
            } else {
                lockPiece(field, currentPiece, rotation, posX, posY);
                clearLines(field);
                currentPiece = nextPiece;
                nextPiece = std::rand() % 7;
                rotation = 0;
                posX = FIELD_WIDTH / 2 - 2;
                posY = 0;
                if (!doesFit(field, currentPiece, rotation, posX, posY))
                    gameOver = true;
            }
            timer = 0.0f;
        }
        render(field, currentPiece, rotation, posX, posY);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    disableRawMode();
    std::cout << "\nGame Over!\n";
    return 0;
}
