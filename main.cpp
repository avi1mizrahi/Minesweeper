#include <iostream>

#include "Minesweeper.h"

int main() {
    unsigned size, n_mines;
    using std::cin, std::cout, std::endl;

    cout << "WELCOME TO  - M I N E S W E E P E R -" << endl;
    cout << "Enter the grid width: ";
    cin >> size;
    cout << endl << "Enter the number of mines: ";
    cin >> n_mines;
    cout << endl;

    Minesweeper minesweeper(size, n_mines);
    minesweeper.print(cout, Minesweeper::reveal);

    cout << "Now, give x,y sequentially" << endl;

    while (minesweeper.state() == Minesweeper::GameState::ONGOING) {
        cout << minesweeper << endl;
        unsigned x, y;
        cin >> x >> y;
        try {
            minesweeper.click(x, y);
        } catch (std::out_of_range&) {
            cout << "out of range, try again." << endl;
        }
    }

    minesweeper.print(cout, Minesweeper::reveal);
    cout << (minesweeper.state() == Minesweeper::GameState::WIN ? "WIN!!!" : "LOST :(") << endl;

    return 0;
}
