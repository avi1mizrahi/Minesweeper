//
// Created by Avi on 11/02/2024.
//

#ifndef RANDOM_H
#define RANDOM_H
#include <vector>
#include <random>


class Random {
    std::random_device rd; // a seed source for the random number engine
    std::mt19937 gen{rd()}; // mersenne_twister_engine seeded with rd()

public:
    std::vector<unsigned> draw_without_replacement(unsigned n, unsigned k) {
        std::vector<unsigned> drawn;

        for (int i = 0; i < k; ++i) {
            auto e = std::uniform_int_distribution<unsigned>(0, n - i - 1)(gen);
            int j = 0;
            for (; j < i; ++j, ++e) {
                if (e < drawn[j]) break;
            }
            drawn.insert(drawn.begin() + j, e);
        }

        return drawn;
    }
};


#endif //RANDOM_H
