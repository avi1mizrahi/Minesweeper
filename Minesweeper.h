//
// Created by Avi on 11/02/2024.
//

#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <vector>

#include "Grid.h"


struct Cell {
    bool mine_{false};
    bool digged_{false};
    bool flagged_{false};

    void setMine() { mine_ = true; }
    void flag() { flagged_ = true; }
    void click() { digged_ = true; }
};

class Minesweeper {
    Grid<Cell> grid_;

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
