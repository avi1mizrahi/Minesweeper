#include <iostream>

#include "Minesweeper.h"

int main() {
    unsigned size, n_mines;
    std::cout << "WELCOME TO  - M I N E S W E E P E R -" << std::endl;
    std::cout << "Enter the grid width: ";
    std::cin >> size;
    std::cout << std::endl << "Enter the number of mines: ";
    std::cin >> n_mines;
    std::cout << std::endl;

    Minesweeper minesweeper(size, n_mines);
    minesweeper.print(std::cout, Minesweeper::reveal);

    std::cout << "Now, give x,y sequentially" << std::endl;

    while (minesweeper.state() == Minesweeper::GameState::ONGOING) {
        std::cout << minesweeper << std::endl;
        unsigned x, y;
        std::cin >> x >> y;
        minesweeper.click(x, y);
    }

    minesweeper.print(std::cout, Minesweeper::reveal);
    std::cout << (minesweeper.state() == Minesweeper::GameState::WIN ? "WIN!!!" : "LOST :(") << std::endl;

    return 0;
}
