//
// Created by Avi on 12/02/2024.
//

#ifndef GRID_H
#define GRID_H
#include <vector>


template <typename T>
class Grid {
    using Row = std::vector<T>;
    std::vector<Row> grid_;

    [[nodiscard]] bool inBounds(int x, int y) const {
        return x < grid_.size() && y < grid_.size();
    }

public:
    explicit Grid(unsigned dim) {
        const Row default_row(dim);
        for (int i = 0; i < dim; ++i) {
            grid_.push_back(default_row);
        }
    }

    T& get(unsigned x, unsigned y) {
        if (!inBounds(x, y)) throw std::out_of_range("out of grid bounds");
        return grid_[x][y];
    }

    void neigboors(unsigned x, unsigned y, std::function<void(T&)> visit) {
        for (int dx = -1; dx <= 1; ++dx) {
            const int vx = x + dx;
            for (int dy = -1; dy <= 1; ++dy) {
                const int vy = y + dy;
                if (vx == x && vy == y) continue;
                if (inBounds(vx, vy)) {
                    visit(grid_[vx][vy]);
                }
            }
        }
    }

    void iterate(std::function<void(const T&)> visit, std::function<void()> row_end) const {
        for (const auto& row : grid_) {
            for (const auto& cell : row) {
                visit(cell);
            }
            row_end();
        }
    }
};


#endif //GRID_H
