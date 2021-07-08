#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <vector>
#include "SudokuBoard.h"


std::vector<std::vector<int>> fetchBoard();


int main() {
    std::vector<std::vector<int>> b = fetchBoard();
    SudokuBoard board(b);

    board.printBoard();

    return 0;
}


std::vector<std::vector<int>> fetchBoard() {
    std::ifstream infile;
    std::string file = "examples.txt";
    infile.open(file.c_str());

    if (infile.fail()) {
        std::cout << "Error opening input data file" << std::endl;
        std::cout << "press enter to exit";
        std::cin.get();
        exit(1);
    }

    std::srand(std::time(nullptr));
    int random = (std::rand() % 50) * 10 + 2;
    int idx = 2;
    std::vector<std::vector<int>> board;
    std::string vals;

    while (infile >> vals) {
        if (idx == random) {
            for (int i = 0; i < 10; ++i) {
                std::vector<int> row;

                for (int j = 0; j < 10; ++j) {
                    row.push_back((int) vals[j]);
                }

                board.push_back(row);
            }

            break;
        }

        idx += 10;
    }

    infile.close();

    return board;
}
