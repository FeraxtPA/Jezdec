#pragma once

#include "Board.h"
#include <stack>
#include <limits>

class Knight {
public:
    int x, y, moveCount;

    inline static const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    inline static const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    Knight(int startX, int startY);

    void move(int newX, int newY);
    bool knightTourStep(Board& board);
    void backtrack(Board& board, std::stack<std::pair<int, int>>& moveStack);
    int WarnsdorffCount(int x, int y, Board& board);
};

