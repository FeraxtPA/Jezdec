#pragma once

#include "Board.h"
#include <stack>
#include <limits>
#include <cmath>

class Knight {
public:
    int x, y, moveCount;

    inline static const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    inline static const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    Knight(int startX, int startY);

    void Move(int newX, int newY);
    bool KnightTourStep(Board& board, std::stack<std::pair<int, int>>& moveStack);
    int WarnsdorffCount(int x, int y, Board& board);
    double EuclideanDistance(int x1, int y1, int x2, int y2);
};

