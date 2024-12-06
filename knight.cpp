#include "Knight.h"
#include "Board.h"
#include <iostream>

Knight::Knight(int startX, int startY)
    : x(startX),
    y(startY),
    moveCount(1)
{
}

void Knight::Move(int newX, int newY) {
    x = newX;
    y = newY;
    moveCount++;
}

int Knight::WarnsdorffCount(int x, int y, Board& board) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx >= 0 && nx < board.m_BoardSize && ny >= 0 && ny < board.m_BoardSize && board.m_Board[nx][ny] == -1) {
            count++;
        }
    }
    return count;
}

double Knight::EuclideanDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool Knight::KnightTourStep(Board& board, std::stack<std::pair<int, int>>& moveStack) {
    int minOnwardMoves = std::numeric_limits<int>::max();
    double maxDistance = -1.0;
    int bestMove = -1;
    int nx = -1, ny = -1;

    int centerX = (board.m_BoardSize - 1) / 2;
    int centerY = (board.m_BoardSize - 1) / 2;

    // Try all possible moves
    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 0 && tx < board.m_BoardSize &&
            ty >= 0 && ty < board.m_BoardSize &&
            board.m_Board[tx][ty] == -1) {  // Only consider unvisited positions


            int onwardMoves = WarnsdorffCount(tx, ty, board);
            double distance = EuclideanDistance(tx, ty, centerX, centerY);

            if (onwardMoves < minOnwardMoves ||
                (onwardMoves == minOnwardMoves && distance > maxDistance)) {
                minOnwardMoves = onwardMoves;
                maxDistance = distance;
                nx = tx;
                ny = ty;
                bestMove = i;
            }
        }
    }

    if (bestMove != -1) {
        // Make the best move
        Move(nx, ny);
        board.MarkPosition(nx, ny, moveCount);
        moveStack.push({ nx, ny });
        return true;
    }

   
    return false;
}













