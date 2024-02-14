//
// Created by Avi on 11/02/2024.
//

#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "Grid.h"


class Cell {
    int mines_around{0};
    bool mine{false};
    bool digged{false};

public:
    void setMine() { mine = true; }
    bool dig();
    bool hasMine() const { return mine; }
    bool hasMinesAround() const { return mines_around != 0; }
    void informMineAround() { ++mines_around; }

    std::string toString(bool reveal = false) const;
};

class Minesweeper {
public:
    enum class GameState {
        ONGOING,
        WIN,
        LOST
    };

private:
    Grid<Cell> grid_;
    unsigned n_unknown;
    GameState state_{GameState::ONGOING};

    void propagateClick(Grid<Cell>::CellRef ref);

    void print(std::ostream& os, bool reveal);

public:
    explicit Minesweeper(unsigned dim, unsigned n_mines);

    void click(unsigned x, unsigned y);

    static class Reveal {} reveal;

    void print(std::ostream& os) { print(os, false); }

    void print(std::ostream& os, Reveal) { print(os, true); }

    [[nodiscard]]
    GameState state() const { return state_; }
};

inline std::ostream& operator<<(std::ostream& os, Minesweeper& ms) {
    ms.print(os);
    return os;
}


#endif //MINESWEEPER_H
