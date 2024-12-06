#include "raylib.h"
#include "Board.h"
#include "Knight.h"
#include <stack>
#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // Check if the number of arguments is correct
    if (argc != 4) {
        std::cout << "Invalid arguments. Usage: <program> <board_size> <start_x> <start_y>" << std::endl;
        return 1;  
    }

   
    int boardSize = strtol(argv[1], NULL, 10);
    int startX = strtol(argv[2], NULL, 10);
    int startY = strtol(argv[3], NULL, 10);

  
    if (startX < 0 || startY < 0 || startX >= boardSize || startY >= boardSize) {
        std::cout << "Invalid starting position. The starting position must be within the board boundaries." << std::endl;
        return 1;  
    }

    const int windowSize = 800;
    int squareSize = windowSize / boardSize;

    InitWindow(800 + 300, 800, "Knight's Tour");

    int frameRate = 60;
    SetTargetFPS(frameRate);  

    Board board(boardSize, squareSize);
    Knight knight(startX, startY);
    board.MarkPosition(knight.x, knight.y, knight.moveCount);

    std::stack<std::pair<int, int>> moveStack;
    moveStack.push({ knight.x, knight.y });

    bool waitingForNextMove = true;
    bool solutionFound = false;
    bool noSolution = false;
    bool isManual = true;

    while (!WindowShouldClose()) {

        
        if (IsKeyPressed(KEY_UP)) {
            frameRate += 5;  
            if (frameRate > 240) {
                frameRate = 240;  
            }
            SetTargetFPS(frameRate); 
            std::cout << "Frame rate: " << frameRate << " FPS" << std::endl;
        }

        if (IsKeyPressed(KEY_DOWN)) {
            frameRate -= 5;  
            if (frameRate < 5) {
                frameRate = 5;  
            }
            SetTargetFPS(frameRate);  
            std::cout << "Frame rate: " << frameRate << " FPS" << std::endl;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        board.Draw();

        if (!solutionFound && !noSolution) {
            if (waitingForNextMove) {
                if (IsKeyPressed(KEY_ENTER) || !isManual) {
                    
                    if (!knight.KnightTourStep(board, moveStack)) {
                        if (moveStack.empty()) {
                            std::cout << "No solution exists for the given board size and starting position." << std::endl;
                            noSolution = true;
                        }
                        else
                        {
                            //TODO try backracking
                        }
                    }

                
                    if (knight.moveCount == boardSize * boardSize) {
                        std::cout << "Solution found!" << std::endl;
                        solutionFound = true;
                    }

                 
                    if (isManual) {
                        waitingForNextMove = false;
                    }
                }

                // Toggle between manual and automatic mode when 'M' is pressed
                if (IsKeyPressed(KEY_M)) {
                    isManual = !isManual;
                    std::cout << (isManual ? "Manual Mode" : "Automatic Mode") << std::endl;
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
