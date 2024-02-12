cmake_minimum_required(VERSION 3.28)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minesweeper main.cpp
        Minesweeper.cpp
        Minesweeper.h
        Random.h
        Grid.h)
