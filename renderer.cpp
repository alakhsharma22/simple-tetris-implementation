#include "renderer.h"
#include "tetris.h"
#include <iostream>

void render(const std::vector<int>& field, int currentPiece, int rotation, int posX, int posY) {
    std::cout << "\033[H\033[J";

    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        std::cout << '*';
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            bool occupied = field[y * FIELD_WIDTH + x];
            for (int px = 0; px < 4; ++px)
            for (int py = 0; py < 4; ++py) {
                int pi = rotateIndex(px, py, rotation);
                if (tetromino[currentPiece][pi] == 'X' && x == posX + px && y == posY + py)
                    occupied = true;
            }
            std::cout << (occupied ? "[]" : "  ");
        }
        std::cout << "*\n";
    }
    std::cout << "Use ← → to move, ↑ to rotate, ↓ to drop, q to quit\n";
}
