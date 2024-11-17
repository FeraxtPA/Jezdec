#include "Board.h"
#include "raylib.h"

Board::Board(int size, int square) : m_BoardSize(size), m_SquareSize(square) {
    m_Board.resize(m_BoardSize, std::vector<int>(m_BoardSize, -1));
}

void Board::Draw() {
    for (int x = 0; x < m_BoardSize; x++) {
        for (int y = 0; y < m_BoardSize; y++) {
            Color color = (x + y) % 2 == 0 ? BEIGE : BROWN;
            DrawRectangle(x * m_SquareSize, y * m_SquareSize, m_SquareSize, m_SquareSize, color);
            if (m_Board[x][y] != -1) {
                DrawText(TextFormat("%d", m_Board[x][y]), x * m_SquareSize + m_SquareSize / 2 - 10,
                    y * m_SquareSize + m_SquareSize / 2 - 10, 20, BLUE);
            }
        }
    }
}

void Board::MarkPosition(int x, int y, int moveCount) {
    m_Board[x][y] = moveCount;
}

void Board::ResetPosition(int x, int y) {
    m_Board[x][y] = -1;
}