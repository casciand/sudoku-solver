#include <iostream>
#include <vector>


const int LENGTH = 9;
const int WIDTH = 9;
const std::pair<int, int> NO_OPEN = {-1, -1};


void printBoard(std::vector<std::vector<int>> board);
bool isValid(std::vector<std::vector<int>> board, int val, std::pair<int, int> coord);
std::pair<int, int> findOpen(std::vector<std::vector<int>> board);
bool solveBoard(std::vector<std::vector<int>> &board);


int main() {
    std::vector<std::vector<int>> board =
            {{1, 0, 0, 0, 8, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 9, 0, 4, 1},
             {0, 4, 3, 0, 0, 0, 9, 0, 6},
             {0, 1, 8, 0, 9, 0, 0, 2, 0},
             {4, 0, 7, 0, 2, 3, 0, 0, 0},
             {0, 0, 0, 0, 0, 4, 6, 0, 0},
             {0, 0, 0, 7, 0, 8, 3, 0, 0},
             {9, 0, 4, 1, 0, 5, 8, 6, 2},
             {3, 8, 5, 9, 0, 2, 0, 7, 4}};

    printBoard(board);
    solveBoard(board);
    printBoard(board);

    return 0;
}


void printBoard(std::vector<std::vector<int>> board) {
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


bool isValid(std::vector<std::vector<int>> board, int val, std::pair<int, int> coord) {
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


std::pair<int, int> findOpen(std::vector<std::vector<int>> board) {
    for (int i = 0; i < LENGTH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (board[i][j] == 0) {
                return {i, j};
            }
        }
    }

    return {-1, -1};
}


bool solveBoard(std::vector<std::vector<int>> &board) {
    if (findOpen(board) == NO_OPEN) {
        return true;
    }

    std::pair<int, int> next = findOpen(board);

    for (int i = 1; i <= 9; ++i) {
        if (isValid(board, i, next)) {
            board[next.first][next.second] = i;

            if (solveBoard(board)) {
                return true;
            }
        }
    }

    board[next.first][next.second] = 0;

    return false;
}
