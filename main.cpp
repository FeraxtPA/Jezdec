#include "raylib.h"
#include "Board.h"
#include "Knight.h"
#include "stack"
#include "iostream"

int main() {
    

    int boardSize = 5;  
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

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        board.Draw();

       
        if (!solutionFound) {
            if (waitingForNextMove) {
                if (IsKeyPressed(KEY_ENTER)) {
                    
                    if (!knight.knightTourStep(board)) {
                        knight.backtrack(board, moveStack);
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

    CloseWindow();  
    return 0;
}
