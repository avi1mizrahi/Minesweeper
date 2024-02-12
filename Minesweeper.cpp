//
// Created by Avi on 11/02/2024.
//
#include <ostream>

#include "Minesweeper.h"

#include "Random.h"

std::string cellChar(Cell cell) {
    switch (cell) {
    case Cell::EMPTY:
        return " ";
    case Cell::MINE:
        return "X";
    case Cell::FLAG:
        return "p";
    case Cell::CLEARED:
        return "o";
    case Cell::EXPLODED:
        return "@";
    }
    return " ";
}

Minesweeper::Minesweeper(unsigned dim, unsigned n_mines) {
    {
        const auto row = std::vector(dim, Cell::EMPTY);
        for (int i = 0; i < dim; ++i) {
            matrix_.push_back(row);
        }
    }

    {
        auto mines_loc = Random().draw_without_replacement(dim * dim, n_mines);
        for (unsigned loc : mines_loc)
            matrix_[loc / dim][loc % dim] = Cell::MINE;
    }
}

void Minesweeper::click(unsigned x, unsigned y) {
    if (x >= matrix_.size() || y >= matrix_.size())
        throw std::runtime_error("x or y out of bounds");

    auto cell = matrix_[x][y];
    switch (cell) {
    case Cell::EMPTY:
        break;
    case Cell::MINE:
        break;
    case Cell::FLAG:
        break;
    case Cell::CLEARED:
        break;
    case Cell::EXPLODED:
        break;
    }
}

void Minesweeper::print(std::ostream& os) const {
    for (const auto& row : matrix_) {
        for (const auto& cell : row) {
            os << cellChar(cell) << ' ';
        }
        os << std::endl;
    }
}
