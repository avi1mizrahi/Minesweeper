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

Minesweeper::Minesweeper(unsigned dim, unsigned n_mines) {
    {
        const Row default_row(dim);
        for (int i = 0; i < dim; ++i) {
            grid_.push_back(default_row);
        }
    }
    {
        auto mines_loc = Random().draw_without_replacement(dim * dim, n_mines);
        for (unsigned loc : mines_loc)
            grid_[loc / dim][loc % dim].setMine();
    }
}

void Minesweeper::click(unsigned x, unsigned y) {
    if (x >= grid_.size() || y >= grid_.size())
        throw std::runtime_error("x or y out of bounds");

    grid_[x][y].click();
}

void Minesweeper::print(std::ostream& os) const {
    for (const auto& row : grid_) {
        for (const auto& cell : row) {
            os << cellChar(cell) << ' ';
        }
        os << std::endl;
    }
}
