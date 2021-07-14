#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include <iostream>
#include <vector>


const int LENGTH = 9;
const int WIDTH = 9;
const std::pair<int, int> NO_OPEN(-1, 1);


class SudokuBoard {
private:

    std::vector<std::vector<int>> board;

    bool isValid(int val, std::pair<int, int> coord) const;
    std::pair<int, int> findOpen() const;
    void traceSolver() const;

public:

    SudokuBoard(std::vector<std::vector<int>> &board);

    void printBoard() const;
    bool solveBoard(bool trace);
};


#endif //SUDOKUBOARD_H
