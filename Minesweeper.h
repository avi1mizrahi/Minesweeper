//
// Created by Avi on 11/02/2024.
//

#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <vector>


enum class Cell {
    EMPTY = 0,
    MINE = 1,
    FLAG = 2,
    CLEARED = 3,
    EXPLODED = 4,
};

std::string cellChar(Cell cell);


class Minesweeper {
    std::vector<std::vector<Cell>> matrix_;
public:
    explicit Minesweeper(unsigned dim, unsigned n_mines);

    void click(unsigned x, unsigned y);

    void print(std::ostream& os) const;
};

inline std::ostream& operator<<(std::ostream& os, const Minesweeper& ms) {
    ms.print(os);
    return os;
}


#endif //MINESWEEPER_H
