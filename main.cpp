#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include "SudokuBoard.h"


std::vector<std::vector<int>> fetchBoard();


int main() {
    std::cout << "Welcome to Sudoku Solver!" << std::endl;
    std::cout << "Would you like to solve a board? (y/n): ";

    std::string ans;
    std::cin >> ans;

    while (ans[0] == 'y' || ans[0] == 'Y') {
        std::vector<std::vector<int>> b = fetchBoard();
        SudokuBoard board(b);

        std::cout << "\nThis is the board to be solved:" << std::endl;
        board.printBoard();
        std::cout << "\nWould you like to trace the algorithm? (y/n): ";
        std::cin >> ans;
        bool trace;

        if (ans[0] == 'y' || ans[0] == 'Y') {
            trace = true;
        } else {
            trace = false;
        }

        board.solveBoard(trace);

        if (!trace) {
            board.printBoard();
        }

        std::cout << "\nBoard solved!" << std::endl;
        std::cout << "\nWould you like to solve another? (y/n): ";
        std::cin >> ans;
    }

    return 0;
}


std::vector<std::vector<int>> fetchBoard() {
    std::string str;
    std::ifstream file("examples.txt");

    // check if file opened properly
    if (!file) {
        std::cout << "Unable to open file. Press enter to exit program.";
        getline(std::cin, str);
        std::cin.get();
        exit(1);
    }

    std::srand(std::time(nullptr));  // use time as seed
    int idx = (std::rand() % 15) * 10 + 2;
    int val;

    for (int s = 1; s < idx; ++s) {
        std::getline(file, str); // skip lines to reach board
    }

    std::vector<std::vector<int>> board;

    for (int i = 0; i < 9; ++i) {
        std::vector<int> row;

        for (int j = 0; j < 9; ++j) {
            file >> val;
            row.push_back(val);
        }

        board.push_back(row);
    }

    file.close();

    return board;
}
