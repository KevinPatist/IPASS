#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

#include "hwlib.hpp"
#include "leds.hpp"
#include "buttonGrid.hpp"

class minesweeper {
private:
    std::array<std::array<int, 8>, 8> field = {
        {   
            {-2, 3, 2, 2, -2, 1, -1, -1},
            {3, -2, -2, 2, 1, 1, -1, -1},
            {-2, 3, 3, 2, 1, -1, -1, -1},
            {1, 1, 2, -2, 2, -1, 1, 1},
            {-1, -1, 2, -2, 2, -1, 1, -2},
            {1, 1, 2, 1, 1, -1, 1, 1},
            {1, -2, 1, -1, 1, 1, 1, -1},
            {1, 1, 1, -1, 1, -2, 1, -1}

            
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
    due::pin_in flagButton;
    bool lastFlagButtonState = false;
    bool flagMode = false;
    bool bombHit = false;
    bool complete = false;

public:
    minesweeper(ledGrid &grid, std::array<hwlib::target::pin_in *, 8> &rowList, std::array<hwlib::target::pin_out *, 8> &columnList, due::pins flagpin):
        gameGrid( grid ),
        rowList( rowList ),
        columnList( columnList ),
        flagButton( due::pin_in(flagpin) )
    {}

    void gameInit();
    
    void flagToggle();

    void changeLedState(int Xcoord, int Ycoord);

    void updateField();

    void gameLoop();
};

#endif // MINESWEEPER_HPP