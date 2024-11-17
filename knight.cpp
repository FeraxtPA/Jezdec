#include "Knight.h"
#include "Board.h"

Knight::Knight(int startX, int startY)
    :x(startX),
     y(startY),
     moveCount(0)
{
}

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

bool Knight::knightTourStep(Board& board) {
    int minOnwardMoves = std::numeric_limits<int>::max();
    int bestMove = std::numeric_limits<int>::min();
    int nx = std::numeric_limits<int>::min();
    int ny = std::numeric_limits<int>::min();

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
        return true;
    }

    return false;
}

void Knight::backtrack(Board& board, std::stack<std::pair<int, int>>& moveStack) {
    while (!moveStack.empty()) {
        auto lastMove = moveStack.top();
        moveStack.pop();
        x = lastMove.first;
        y = lastMove.second;
        board.ResetPosition(x, y);
        moveCount--;

        if (knightTourStep(board)) {
            return;
        }
    }
}
