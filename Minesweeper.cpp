//
// Created by Avi on 11/02/2024.
//
#include <ostream>

#include "Minesweeper.h"

#include <iomanip>

#include "Random.h"

bool Cell::dig() {
    auto was = digged;
    digged = true;
    return was;
}

std::string Cell::toString(bool reveal) const {
    if (!digged && !reveal) return "[ ]";
    if (mine) {
        return "[@]";
    }
    if (mines_around) {
        return "[" + std::to_string(mines_around) + "]";
    }
    return "   ";
}

Minesweeper::Minesweeper(unsigned dim, unsigned n_mines) : grid_(dim), n_unknown(dim*dim - n_mines) {
    const auto mines_loc = Random().draw_without_replacement(dim * dim, n_mines);
    for (const unsigned loc : mines_loc)
        grid_.get(loc / dim, loc % dim).cell.setMine();

    grid_.iterate(
        [this](auto cellref) {
            grid_.neigboors(cellref, [&cellref](auto neighboor) {
                if (neighboor.cell.hasMine())
                    cellref.cell.informMineAround();
            });
        },
        [] {},
        [] {}
    );
}

void Minesweeper::propagateClick(const Grid<Cell>::CellRef ref) {
    auto& cell = ref.cell;

    if (cell.dig()) {
        return;
    }

    --n_unknown;

    if (cell.hasMine()) {
        state_ = GameState::LOST;
        return;
    }
    if (!n_unknown) {
        state_ = GameState::WIN;
    }
    if (cell.hasMinesAround()) {
        return;
    }

    grid_.neigboors(ref, [this](auto neighboor) {
        propagateClick(neighboor);
    });
}

void Minesweeper::click(unsigned x, unsigned y) {
    propagateClick(grid_.get(x, y));
}

void Minesweeper::print(std::ostream& os, bool reveal) {
    constexpr unsigned first_col_width = 4;
    os << std::string(first_col_width, ' ');
    for (int i = 0; i < grid_.dim(); ++i) {
        os << " " << i << " ";
    }
    os << std::endl;
    unsigned i_row = 0;
    grid_.iterate(
        [&os, this, reveal](auto cellref) {
            os << cellref.cell.toString(reveal);
        },
        [&os, &i_row] { os << std::setw(first_col_width-1) << " " << i_row++ ; },
        [&os] { os << std::endl; }
    );
}
