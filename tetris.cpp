#include "tetris.h"
#include <cstdlib>

const char* tetromino[7] = {
    // I
    "..X."
    "..X."
    "..X."
    "..X.",
    // Z
    "..X."
    ".XX."
    ".X.."
    "....",
    // S
    ".X.."
    ".XX."
    "..X."
    "....",
    // O
    "...."
    ".XX."
    ".XX."
    "....",
    // L
    "..X."
    "..X."
    ".XX."
    "....",
    // J
    ".X.."
    ".X.."
    ".XX."
    "....",
    // T
    ".X.."
    ".XX."
    ".X.."
    "...."
};

int rotateIndex(int px, int py, int r) {
    switch (r & 3) {
        case 0: return py * 4 + px;
        case 1: return 12 + py - (px * 4);
        case 2: return 15 - (py * 4) - px;
        case 3: return 3 - py + (px * 4);
    }
    return 0;
}

bool doesFit(const std::vector<int>& field, int piece, int rotation, int posX, int posY) {
    for (int px = 0; px < 4; ++px)
    for (int py = 0; py < 4; ++py) {
        int pi = rotateIndex(px, py, rotation);
        if (tetromino[piece][pi] == 'X') {
            int fx = posX + px;
            int fy = posY + py;
            if (fx < 0 || fx >= FIELD_WIDTH || fy < 0 || fy >= FIELD_HEIGHT)
                return false;
            if (field[fy * FIELD_WIDTH + fx])
                return false;
        }
    }
    return true;
}

void lockPiece(std::vector<int>& field, int piece, int rotation, int posX, int posY) {
    for (int px = 0; px < 4; ++px)
    for (int py = 0; py < 4; ++py) {
        int pi = rotateIndex(px, py, rotation);
        if (tetromino[piece][pi] == 'X') {
            int fx = posX + px;
            int fy = posY + py;
            if (fx >= 0 && fx < FIELD_WIDTH && fy >= 0 && fy < FIELD_HEIGHT)
                field[fy * FIELD_WIDTH + fx] = 1;
        }
    }
}

int clearLines(std::vector<int>& field) {
    int lines = 0;
    for (int y = 0; y < FIELD_HEIGHT; ++y) {
        bool full = true;
        for (int x = 0; x < FIELD_WIDTH; ++x) {
            if (!field[y * FIELD_WIDTH + x]) {
                full = false;
                break;
            }
        }
        if (full) {
            ++lines;
            for (int row = y; row > 0; --row)
                for (int x = 0; x < FIELD_WIDTH; ++x)
                    field[row * FIELD_WIDTH + x]
                      = field[(row - 1) * FIELD_WIDTH + x];
            for (int x = 0; x < FIELD_WIDTH; ++x)
                field[x] = 0;
        }
    }
    return lines;
}
