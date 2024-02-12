//
// Created by Avi on 11/02/2024.
//
#include <ostream>

#include "Minesweeper.h"

#include <cassert>
#include <iomanip>

#include "Random.h"

std::ostream& operator<<(std::ostream& o, const Grid<Cell>::CellRef& ref) {
    ref.print(o);
    return o;
}

std::string cellChar(const Cell cell, bool reveal=false) {
    if (cell.digged || reveal) {
        if (cell.mine) {
            return "[@]";
        }
        if (cell.mines_around) {
            return "[" + std::to_string(cell.mines_around) + "]";
        }
        return "[ ]";
    }
    return "[.]";
}

Minesweeper::Minesweeper(unsigned dim, unsigned n_mines) : grid_(dim), n_unknown(dim*dim - n_mines) {
    const auto mines_loc = Random().draw_without_replacement(dim * dim, n_mines);
    for (const unsigned loc : mines_loc)
        grid_.get(loc / dim, loc % dim).cell.setMine();

    grid_.iterate(
        [this](auto cellref) {
            grid_.neigboors(cellref, [&cellref](auto neighboor) {
                if (neighboor.cell.mine)
                    ++cellref.cell.mines_around;
            });
        },
        [] {},
        [] {}
    );
}

void Minesweeper::propagateClick(const Grid<Cell>::CellRef ref) {
    auto& cell = ref.cell;
    const bool propagate = cell.mines_around == 0 && !cell.digged;

    if (!cell.digged) {
        cell.dig();
        --n_unknown;
    }
    if (!n_unknown) {
        state_ = GameState::WIN;
    }

    assert(!cell.mine);

    if (!propagate) return;

    grid_.neigboors(ref, [this](auto neighboor) {
        propagateClick(neighboor);
    });
}

void Minesweeper::click(unsigned x, unsigned y) {
    const auto cellref = grid_.get(x, y);

    if (cellref.cell.mine) {
        state_ = GameState::LOST;
        return;
    }

    propagateClick(cellref);
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
            os << cellChar(cellref.cell, reveal);
        },
        [&os, &i_row] { os << std::setw(first_col_width-1) << " " << i_row++ ; },
        [&os] { os << std::endl; }
    );
}
