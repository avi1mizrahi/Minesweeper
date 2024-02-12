//
// Created by Avi on 11/02/2024.
//
#include <ostream>

#include "Minesweeper.h"

#include "Random.h"

std::string cellChar(Cell cell) {
    if (cell.digged_) {
        return "[o]";
    }
    if (cell.flagged_) {
        return "[P]";
    }
    if (cell.mine_) {
        return "[X]";
    }
    return "[ ]";
}

Minesweeper::Minesweeper(unsigned dim, unsigned n_mines) : grid_(dim) {
    const auto mines_loc = Random().draw_without_replacement(dim * dim, n_mines);
    for (const unsigned loc : mines_loc)
        grid_.get(loc / dim, loc % dim).setMine();
}

void Minesweeper::click(unsigned x, unsigned y) {
    grid_.get(x, y).click();
}

void Minesweeper::print(std::ostream& os) const {
    grid_.iterate(
        [&os](const Cell& cell) { os << cellChar(cell); },
        [&os]() { os << std::endl; }
    );
}
