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

    [[nodiscard]]
    bool inBounds(int x, int y) const {
        return x >= 0 && y >= 0 && x < grid_.size() && y < grid_.size();
    }

    [[nodiscard]]
    bool inBounds(unsigned x, unsigned y) const {
        return x < grid_.size() && y < grid_.size();
    }

public:
    class CellRef {
        const unsigned x;
        const unsigned y;

        friend Grid;

    public:
        T& cell;

        CellRef(unsigned x, unsigned y, T& cell): x(x), y(y), cell(cell) {}

        void print(std::ostream& o) const {
            o << "Ref[" << x << "," << y << "]";
        }
    };

    explicit Grid(unsigned dim) {
        const Row default_row(dim);
        for (int i = 0; i < dim; ++i) {
            grid_.push_back(default_row);
        }
    }

    CellRef get(unsigned x, unsigned y) {
        if (!inBounds(x, y)) throw std::out_of_range("out of grid bounds");
        return createRef(x, y);
    }

    void neigboors(CellRef ref, std::function<void(CellRef)> visit) {
        const int refx = static_cast<int>(ref.x);
        const int refy = static_cast<int>(ref.y);

        for (int x = refx - 1; x <= refx + 1; ++x) {
            for (int y = refy - 1; y <= refy + 1; ++y) {
                if (x == refx && y == refy) continue;
                if (inBounds(x, y)) {
                    visit(createRef(x, y));
                }
            }
        }
    }

    void iterate(
        std::function<void(CellRef)> visit,
        const std::function<void()>& row_start,
        const std::function<void()>& row_end
    ) {
        for (int x = 0; x < grid_.size(); ++x) {
            row_start();
            for (int y = 0; y < grid_.size(); ++y) {
                visit(createRef(x, y));
            }
            row_end();
        }
    }

    [[nodiscard]]
    unsigned dim() const { return grid_.size(); }

private:
    CellRef createRef(unsigned x, unsigned y) { return CellRef(x, y, grid_[x][y]); }
};

#endif //GRID_H
