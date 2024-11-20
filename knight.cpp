#include "Knight.h"
#include "Board.h"
#include <iostream>

Knight::Knight(int startX, int startY)
    : x(startX),
    y(startY),
    moveCount(0) {}

void Knight::move(int newX, int newY) {
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

bool Knight::knightTourStep(Board& board, std::stack<std::pair<int, int>>& moveStack) {
    int minOnwardMoves = std::numeric_limits<int>::max();
    int bestMove = -1;
    int nx = -1, ny = -1;

    for (int i = 0; i < 8; i++) {
        int tx = x + dx[i], ty = y + dy[i];
        if (tx >= 0 && tx < board.m_BoardSize && ty >= 0 && ty < board.m_BoardSize && board.m_Board[tx][ty] == -1) {
            int onwardMoves = WarnsdorffCount(tx, ty, board);
            if (onwardMoves < minOnwardMoves) {
                minOnwardMoves = onwardMoves;
                nx = tx;
                ny = ty;
                bestMove = i;
            }
        }
    }

    if (bestMove != -1) {
        move(nx, ny);
        board.MarkPosition(nx, ny, moveCount);
        moveStack.push({ nx,ny });
        return true;
    }

    return false;
}

void Knight::backtrack(Board& board, std::stack<std::pair<int, int>>& moveStack) {
    if (moveStack.empty()) {
        std::cout << "Backtrack stack is empty." << std::endl;
        return;
    }

  
    auto lastMove = moveStack.top();
    moveStack.pop();

   
    board.ResetPosition(x, y);

    board.MarkPosition(x, y, moveCount);
   
    x = lastMove.first;
    y = lastMove.second;

    moveCount--;

    board.MarkPosition(x, y, moveCount);
   

    std::cout << "Backtracking to: (" << x << ", " << y << "), moveCount: " << moveCount << std::endl;

   
    if (!knightTourStep(board, moveStack)) {
        std::cout << "No further moves possible after backtracking." << std::endl;
    }
}



