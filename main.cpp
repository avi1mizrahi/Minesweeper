#include <iostream>

#include "Minesweeper.h"

int main() {
    Minesweeper minesweeper(7, 10);
    std::cout << minesweeper << std::endl;

    minesweeper.click(1,3);
    std::cout << minesweeper << std::endl;

    minesweeper.click(4,4);
    std::cout << minesweeper << std::endl;

    return 0;
}
