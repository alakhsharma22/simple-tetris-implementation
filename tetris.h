#ifndef TETRIS_H
#define TETRIS_H

#include <vector>

constexpr int FIELD_WIDTH  = 10;
constexpr int FIELD_HEIGHT = 20;

extern const char* tetromino[7];

int rotateIndex(int px, int py, int r);

bool doesFit(const std::vector<int>& field, int piece, int rotation, int posX, int posY);

void lockPiece(std::vector<int>& field, int piece, int rotation, int posX, int posY);

int clearLines(std::vector<int>& field);

#endif
