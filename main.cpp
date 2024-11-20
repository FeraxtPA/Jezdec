#include "raylib.h"
#include "Board.h"
#include "Knight.h"
#include <stack>
#include <iostream>

int main() {
    int boardSize = 4;
    int squareSize = 80;

    InitWindow(boardSize * squareSize, boardSize * squareSize, "Knight's Tour");
    SetTargetFPS(60);

    Board board(boardSize, squareSize);
    Knight knight(0, 0);
    knight.move(0, 0);
    board.MarkPosition(knight.x, knight.y, knight.moveCount);

    std::stack<std::pair<int, int>> moveStack;
    moveStack.push({ knight.x, knight.y });

    bool waitingForNextMove = true;
    bool solutionFound = false;
    bool noSolution = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        board.Draw();

        if (!solutionFound && !noSolution) {
            if (waitingForNextMove) {
                if (IsKeyPressed(KEY_ENTER)) {
                    if (!knight.knightTourStep(board, moveStack)) {
                        if (moveStack.empty()) {
                            std::cout << "No solution exists for the given board size and starting position." << std::endl;
                            noSolution = true; 
                        }
                        else {
                            knight.backtrack(board, moveStack);
                        }
                    }

                    if (knight.moveCount == boardSize * boardSize) {
                        std::cout << "Solution found!" << std::endl;
                        solutionFound = true;
                    }

                    waitingForNextMove = false;
                }
            }
            else {
                waitingForNextMove = true;
            }
        }

        EndDrawing();
    }

    if (noSolution) {
        std::cout << "Exiting due to lack of solution." << std::endl;
    }

    CloseWindow();
    return 0;
}
