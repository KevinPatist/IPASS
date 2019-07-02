#ifndef MINESWEEPER_HPP
#define MINESWEEPER_HPP

/// @file

#include "hwlib.hpp"
#include "leds.hpp"
#include "buttonGrid.hpp"

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
        
        {{  {-1, -1, -1, -1, -1, 1, -2, 1},
            {1, 1, -1, -1, -1, 1, 1, 1},
            {-2, 1, -1, -1, 1, 1, 2, 1},
            {2, 3, 1, 1, 1, -2, 2, -2},
            {-2, 2, -2, 1, 1, 2, 3, 2},
            {2, 3, 1, 1, -1, 1, -2, 2},
            {-2, 2, -1, -1, -1, 1, 2, -2},
            {-2, 2, -1, -1, -1, -1, 1, 1}}},
        
        {{  {-1, 1, -2, 2, 1, 1, 1, -2},
            {1, 2, 2, 3, -2, 1, 1, 1},
            {-2, 2, 1, -2, 2, 1, -1, -1},
            {-2, 2, 1, 1, 1, -1, -1, -1},
            {1, 1, -1, -1, -1, 1, 1, 1},
            {1, 1, 1, -1, -1, 1, -2, 1},
            {1, -2, 2, 1, -1, 2, 2, 2},
            {1, 2, -2, 1, -1, 1, -2, 1}}},
        
        {{  {1, -2, 1, -1, -1, -1, 1, 1},
            {2, 2, 1, -1, 1, 1, 2, -2},
            {-2, 1, -1, -1, 1, -2, 2, 1},
            {1, 1, 1, 1, 2, 1, 1, -1},
            {1, 1, 2, -2, 1, -1, -1, -1},
            {1, -2, 3, 2, 1, -1, 1, 1},
            {2, 3, -2, 1, -1, -1, 2, -2},
            {1, -2, 2, 1, -1, -1, 2, -2}}},
        
        {{  {1, -2, 2, 2, -2, 1, 2, -2},
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
    
    /// \brief
    /// A function to check for a buttonpress on a designated flagMode button
    /// \details
    /// This function changes the state of flagMode according to the output of a button\n
    /// Example: minesweeper.flagCheck();\n
    /// This would check flagButton to update flagMode accordingly
    void flagCheck();

    /// \brief
    /// This function is called to update the state of an LED on the active game field
    /// \details
    /// This function changes the current stat of an LED on the field\n
    /// The location of said LED is given using Xcoord and Ycoord\n
    /// Example: minesweeper.changeLedState(4, 5);\n
    /// This would check and update the current state of the LED on coordinate(4,5) according to the field tile at the same location
    void changeLedState(int Xcoord, int Ycoord);

    /// \brief
    /// This function refreshes the LEDs on the grid; 
    /// \details
    /// This function changes the color of the LEDs in the grid according to the ledState array.\n
    /// The ledState array stores the data of the current game field.\n
    /// Example: minesweeper.updateField();\n
    /// This would change the LED colors in gameGrid to be right with the game field.
    void updateField();
    
    /// \brief
    /// This function checks the current state of the playing field to see if the game is completed
    /// \details 
    /// This function checks if the game has been completed by checking if every tile has either been revealed or flagged.\n
    /// Example: minesweeper.completeCheck();\n
    /// This would check each tile in ledState to see if it has either been flagged or revealed.\n
    /// If there is any tile that isn't either revealed or flagged, the "complete" variable will be set to false;
    void completeCheck();
    
    /// \brief
    /// This function draws a trophy on the LED grid
    /// \details
    /// This function draws a trophy on the grid to show the player they won.\n
    /// Example: minesweeper.completeEnd();\n
    /// This would draw a trophy to the gameGrid to show that the player won/completed the game.
    void completeEnd();

    /// \brief
    /// This function draws a big red cross on the LED grid
    /// \details
    /// This function draws a big red cross on the grid to show the player they lost\n
    /// Example: minesweeper.gameOver();\n
    /// This would draw a red cross to the gameGrid to show that the player lost.
    void gameOver();

public:
    /// \brief
    /// Construct the main game object.\n
    /// \details
    /// Example: auto game = minesweeper(LEDgrid, rowLijst, columnLijst, due::pins::d4, due::pins::d3);\n
    /// This would create a minesweeper object which uses LEDgrid as its led grid, rowLijst as rowList, columnLijst as columnList, digital pin 4 as its flag button and digital pin 3 as the flag LED 
    minesweeper(ledGrid &grid, std::array<hwlib::target::pin_in *, 8> &rowList, std::array<hwlib::target::pin_out *, 8> &columnList, due::pins flagpin1, due::pins flagpin2):
        gameGrid( grid ),
        rowList( rowList ),
        columnList( columnList ),
        flagButton( due::pin_in(flagpin1) ),
        flagLed( due::pin_out(flagpin2) )
    {}

    /// This function is used to initialise the LEDs and make sure every pin in columnList is turned off.\n
    /// Example: minesweeper.gameInit();
    void gameInit();
    

    /// \brief
    /// A function including a while-loop for the game and showing either the game over or victory screen
    /// \details
    /// The while loop calls all neccesary functions in the correct order.\n
    /// After the while-loop it calls to the right endscreen (either gameOver() or completeEnd()).\n
    /// Example: minesweeper.gameLoop();\n
    /// This would start the game and end it when its done. 
    void gameLoop();
};

#endif // MINESWEEPER_HPP