#pragma once


#include "raylib.h"
#include <vector>

class Board {
public:
    int m_BoardSize;
    int m_SquareSize;
    std::vector<std::vector<int>> m_Board;

    Board(int size, int square);

    void Draw();
    void MarkPosition(int x, int y, int moveCount);
    void ResetPosition(int x, int y);
   
};


