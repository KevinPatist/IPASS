#include "minesweeper.hpp"

void minesweeper::gameInit() {
    gameGrid.initialise();
    for(auto pin : columnList) {
        pin->write(0);
        pin->flush();
    }
    hwlib::wait_ms(100);
};

void minesweeper::flagToggle() {
    flagButton.refresh();
    if(flagButton.read() != lastFlagButtonState) {
        if(flagButton.read()) {
            flagMode = !flagMode;
            lastFlagButtonState = flagButton.read();
        }
    }
};

void minesweeper::changeLedState(int Xcoord, int Ycoord) {
    if(Xcoord > 0) {
        if(flagMode) {
            if((ledState[Xcoord-1][Ycoord-1] == -3) && coords != lastCoords) {
                ledState[Xcoord-1][Ycoord-1] = 9;
            } else if((ledState[Xcoord-1][Ycoord-1] == 9) && coords != lastCoords) {
                ledState[Xcoord-1][Ycoord-1] = -3;
            }
        } else {
            if((ledState[Xcoord-1][Ycoord-1] == 9) && coords != lastCoords) {
                ledState[Xcoord-1][Ycoord-1] = field[Xcoord-1][Ycoord-1];
                if(field[Xcoord-1][Ycoord-1] == -1) {
                    if((Xcoord-1 > 0 && Ycoord > 0) || (Xcoord-1 < 9 && Ycoord < 9)) {
                        minesweeper::changeLedState(Xcoord-1, Ycoord);
                        hwlib::cout << "done did number 1" << hwlib::endl;
                    }
                    if((Xcoord > 0 && Ycoord > 0) || (Xcoord < 9 && Ycoord < 9)) {
                        minesweeper::changeLedState(Xcoord, Ycoord);
                        hwlib::cout << "done did number 2" << hwlib::endl;
                    }
                    if((Xcoord > 0 && Ycoord-1 > 0) || (Xcoord < 9 && Ycoord-1 < 9)) {
                        minesweeper::changeLedState(Xcoord, Ycoord-1);
                        hwlib::cout << "done did number 3" << hwlib::endl;
                    }
                    if((Xcoord > 0 && Ycoord-2 > 0) || (Xcoord < 9 && Ycoord-2 < 9)) {
                        minesweeper::changeLedState(Xcoord, Ycoord-2);
                        hwlib::cout << "done did number 4" << hwlib::endl;
                    }
                    if((Xcoord-1 > 0 && Ycoord-2 > 0) || (Xcoord-1 < 9 && Ycoord-2 < 9)) {
                        minesweeper::changeLedState(Xcoord-1, Ycoord-2);
                        hwlib::cout << "done did number 5" << hwlib::endl;
                    }
                    if((Xcoord-2 > 0 && Ycoord-2 > 0) || (Xcoord-2 < 9 && Ycoord-2 < 9)) {
                        minesweeper::changeLedState(Xcoord-2, Ycoord-2);
                        hwlib::cout << "done did number 6" << hwlib::endl;
                    }
                    if((Xcoord-2 > 0 && Ycoord-1 > 0) || (Xcoord-2 < 9 && Ycoord-1 < 9)) {
                        minesweeper::changeLedState(Xcoord-2, Ycoord-1);
                        hwlib::cout << "done did number 7" << hwlib::endl;
                    }
                    if((Xcoord-2 > 0 && Ycoord > 0) || (Xcoord-2 < 9 && Ycoord < 9)) {
                        minesweeper::changeLedState(Xcoord-2, Ycoord);
                        hwlib::cout << "done did number 8" << hwlib::endl;
                    }
                    // minesweeper::changeLedState(Xcoord, Ycoord);
                    // minesweeper::changeLedState(Xcoord, Ycoord-1);
                    // minesweeper::changeLedState(Xcoord, Ycoord-2);
                    // minesweeper::changeLedState(Xcoord-1, Ycoord-2);
                    // minesweeper::changeLedState(Xcoord-2, Ycoord-2);
                    // minesweeper::changeLedState(Xcoord-2, Ycoord-1);
                    // minesweeper::changeLedState(Xcoord-2, Ycoord);
                }
            }
        }
    }
};

void minesweeper::updateField() {
    for(int Ypos = 0; Ypos <8; Ypos++) {
        for(int Xpos = 0; Xpos <8; Xpos++) {
            switch(ledState[Xpos][Ypos]) {
                case 9:  gameGrid.changeLedRGB(Xpos+1, Ypos+1, 0, 0, 0);
                         break;
                case -1: gameGrid.changeLedRGB(Xpos+1, Ypos+1, 255, 255, 255);
                         break;
                case 1:  gameGrid.changeLedRGB(Xpos+1, Ypos+1, 0, 255, 195);
                         break;
                case 2:  gameGrid.changeLedRGB(Xpos+1, Ypos+1, 0, 255, 0);
                         break;
                case 3:  gameGrid.changeLedRGB(Xpos+1, Ypos+1, 255, 255, 0);
                         break;
                case 4:  gameGrid.changeLedRGB(Xpos+1, Ypos+1, 255, 127, 0);
                         break;
                case 5:  gameGrid.changeLedRGB(Xpos+1, Ypos+1, 255, 0, 0);
                         break;
                case -2: bombHit = true;
                         break;
                case -3: gameGrid.changeLedRGB(Xpos+1, Ypos+1, 200, 0, 255);
                         break;
                default: gameGrid.changeLedRGB(Xpos+1, Ypos+1, 255, 255, 255);
                         break;
            }; 
            if(bombHit) {
                break;
            };
        }
        if(bombHit) {
            break;
        };
    }
    gameGrid.write();
};

void minesweeper::gameLoop() {
    
    while(!bombHit && !complete) {
        lastCoords = coords;
        minesweeper::flagToggle();
        buttonCheck(columnList, rowList, coords);
        minesweeper::changeLedState(coords[0], coords[1]);
        minesweeper::updateField();
        hwlib::cout << "got through " << coords[0] << " " << coords[1] << hwlib::endl;
        hwlib::wait_ms(50);
    };
    
};