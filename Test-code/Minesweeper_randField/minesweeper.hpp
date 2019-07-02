#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

/// @file

#include "hwlib.hpp"
#include "leds.hpp"
#include "buttonGrid.hpp"
#include <stdlib.h>

/// A class that includes everything needed for the game minesweeper
///
/// It includes all functions and variables needed to run the game on a WS2812B 8x8 LED grid
/// This class uses my WS2812B library for controlling the LEDs
class minesweeper {
private:
    std::array<std::array<std::array<int, 8>, 8>, 5> field = {{
        {{  {-2, 3, 2, 2, -2, 1, -1, -1},
            {3, -2, -2, 2, 1, 1, -1, -1},
            {-2, 3, 3, 2, 1, -1, -1, -1},
            {1, 1, 2, -2, 2, -1, 1, 1},
            {-1, -1, 2, -2, 2, -1, 1, -2},
            {1, 1, 2, 1, 1, -1, 1, 1},
            {1, -2, 1, -1, 1, 1, 1, -1},
            {1, 1, 1, -1, 1, -2, 1, -1}}},
        
        {{   {-1, -1, -1, -1, -1, 1, -2, 1},
            {1, 1, -1, -1, -1, 1, 1, 1},
            {-2, 1, -1, -1, 1, 1, 2, 1},
            {2, 3, 1, 1, 1, -2, 2, -2},
            {-2, 2, -2, 1, 1, 2, 3, 2},
            {2, 3, 1, 1, -1, 1, -2, 2},
            {-2, 2, -1, -1, -1, 1, 2, -2},
            {-2, 2, -1, -1, -1, -1, 1, 1}}},
        
        {{   {-1, 1, -2, 2, 1, 1, 1, -2},
            {1, 2, 2, 3, -2, 1, 1, 1},
            {-2, 2, 1, -2, 2, 1, -1, -1},
            {-2, 2, 1, 1, 1, -1, -1, -1},
            {1, 1, -1, -1, -1, 1, 1, 1},
            {1, 1, 1, -1, -1, 1, -2, 1},
            {1, -2, 2, 1, -1, 2, 2, 2},
            {1, 2, -2, 1, -1, 1, -2, 1}}},
        
        {{   {1, -2, 1, -1, -1, -1, 1, 1},
            {2, 2, 1, -1, 1, 1, 2, -2},
            {-2, 1, -1, -1, 1, -2, 2, 1},
            {1, 1, 1, 1, 2, 1, 1, -1},
            {1, 1, 2, -2, 1, -1, -1, -1},
            {1, -2, 3, 2, 1, -1, 1, 1},
            {2, 3, -2, 1, -1, -1, 2, -2},
            {1, -2, 2, 1, -1, -1, 2, -2}}},
        
        {{   {1, -2, 2, 2, -2, 1, 2, -2},
            {2, 2, 2, -2, 2, 1, 2, -2},
            {-2, 2, 3, 2, 2, -1, 1, 1},
            {2, -2, 2, -2, 1, -1, -1, -1},
            {2, 2, 3, 1, 1, -1, -1, -1},
            {1, -2, 1, -1, -1, -1, -1, -1},
            {2, 2, 2, -1, -1, -1, -1, -1},
            {1, -2, 1, -1, -1, -1, -1, -1}}}
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
    due::pin_out flagLed;
    bool lastFlagButtonState = false;
    bool flagMode = false;
    bool bombHit = false;
    bool complete = false;
    int fieldNum = 0;

public:
    /// Construct the main game object
    minesweeper(ledGrid &grid, std::array<hwlib::target::pin_in *, 8> &rowList, std::array<hwlib::target::pin_out *, 8> &columnList, due::pins flagpin1, due::pins flagpin2):
        gameGrid( grid ),
        rowList( rowList ),
        columnList( columnList ),
        flagButton( due::pin_in(flagpin1) ),
        flagLed( due::pin_out(flagpin2) )
    {}

    /// This function is used to initialise the LEDs and make sure every pin in columnList is turned off
    void gameInit();
    
    /// A function to check for a buttonpress on a designated flagMode button
    /// This function changes the state of flagMode according to the output of a button
    void flagCheck();

    /// This function is called to update the state of an LED on the active game field
    void changeLedState(int Xcoord, int Ycoord);

    /// This function refreshes the LEDs on the grid; 
    void updateField();
    
    /// This function checks the current state of the playing field to see if the game is completed
    void completeCheck();
    
    /// This function draws a trophy on the LED grid to indicate the player completing/winning the game
    void completeEnd();

    /// This function draws a big red cross on the LED grid to indicate the player losing the game
    void gameOver();

    /// A function including a while-loop foor the game and showing either the game over or victory screen
    /// 
    /// The while loop calls all neccesary functions in the correct order
    /// After the while-loop it calls to the right endscreen (either gameOver() or completeEnd())
    void gameLoop();
};

#endif // MINESWEEPER_HPP