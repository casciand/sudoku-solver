#include "SudokuBoard.h"
#include <thread>


SudokuBoard::SudokuBoard(std::vector<std::vector<int>> &board) : board(board) {}


void SudokuBoard::printBoard() const {
    for (size_t i = 0; i < LENGTH; ++i) {
        if (i % 3 == 0) {
            std::cout << std::endl << "| --------------------- |";
        }

        std::cout << std::endl << "| ";

        for (size_t j = 0; j < WIDTH; ++j) {
            std::cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0) {
                std::cout << "| ";
            }
        }
    }

    std::cout << std::endl << "| --------------------- |" << std::endl;
}


bool SudokuBoard::solveBoard(bool trace) {
    if (trace) {
        traceSolver(trace);
    }

    std::pair<int, int> next = findOpen();

    if (next.first == -1 && next.second == -1) {
        return true;  // all spaces filled correctly
    }

    for (int i = 1; i <= 9; ++i) {
        if (isValid(i, next)) {
            board[next.first][next.second] = i;  // set index to next valid value

            if (solveBoard(trace)) {  // move to next available index
                return true;  // board solved
            }

            board[next.first][next.second] = 0;
        }
    }

    return false;  // no solution, backtrack
}


bool SudokuBoard::isValid(int val, std::pair<int, int> coord) const {
    for (int i = 0; i < WIDTH; ++i) {  // checks row
        if (board[coord.first][i] == val) {
            return false;
        }
    }

    for (int i = 0; i < LENGTH; ++i) {  // checks column
        if (board[i][coord.second] == val) {
            return false;
        }
    }

    // get coords of top left of box
    int boxRow = (coord.first / 3) * 3;
    int boxColumn = (coord.second / 3) * 3;

    for (int i = boxRow; i < boxRow + 3; ++i) {
        for (int j = boxColumn; j < boxColumn + 3; ++j) {
            if (board[i][j] == val) {
                return false;
            }
        }
    }

    return true;
}


std::pair<int, int> SudokuBoard::findOpen() const {
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (board[i][j] == 0) {
                return {i, j};
            }
        }
    }

    return {-1, -1};
}


void SudokuBoard::traceSolver(bool trace) const {
    if (trace) {
        #if defined _WIN32
            system("cls");
        #elif defined __APPLE__
            system("clear");
        #endif

        printBoard();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
