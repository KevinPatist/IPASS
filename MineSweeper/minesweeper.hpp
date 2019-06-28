#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "hwlib.hpp"
#include "leds.hpp"
#include "buttonGrid.hpp"

class minesweeper {
private:
    std::array<std::array<int, 8>, 8> field = {
        {   
            {-1, 3, -1, 1, 0, 1, 1, 1},
            {3, -1, 3, 1, 0, 1, -1, 1},
            {2, -1, 2, 2, 2, 2, 1, 1},
            {2, 2, 2, -1, -1, 1, 0, 0},
            {-1, 1, 1, 2, 2, 1, 1, 1},
            {1, 1, 0, 0, 0, 0, 1, -1},
            {0, 0, 0, 1, 1, 1, 1, 1},
            {0, 0, 0, 1, -1, 1, 0, 0}

            // {0, 1, 1, 1, 0, 0, 0, 0},
            // {0, 2, -1, 2, 0, 1, 2, 2},
            // {1, 3, -1, 2, 0, 1, -1, -1},
            // {-1, 3, 1, 1, 0, 1, 2, 2},
            // {-1, 2, 0, 1, 1, 1, 0, 0},
            // {1, 1, 0, 1, -1, 2, 1, 0},
            // {0, 0, 0, 1, 3, -1, 3, 1},
            // {0, 0, 0, 0, 2, -1, 3, -1}
        }
    };

    ledGrid &gameGrid;
    std::array<int, 2> coords = {0,0};
    std::array<int, 2> lastCoords = {0,0};
    std::array<std::array<int, 8>, 8> ledState = {{{9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9},
                                                   {9, 9, 9, 9, 9, 9, 9, 9}}};

    std::array<hwlib::target::pin_in *, 8> &rowList;
    std::array<hwlib::target::pin_out *, 8> &columnList;
    bool flagMode = false;

public:
    minesweeper(ledGrid &grid, std::array<hwlib::target::pin_in *, 8> &rowList, std::array<hwlib::target::pin_out *, 8> &columnList):
        gameGrid( grid ),
        rowList( rowList ),
        columnList( columnList )
    {}

    void gameInit();
    
    void gameLoop();
};

#endif // MINESWEEPER_HPP