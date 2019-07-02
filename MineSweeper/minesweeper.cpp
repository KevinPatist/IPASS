#include "minesweeper.hpp"

void minesweeper::gameInit() {
    
    gameGrid.initialise();
    for(auto pin : columnList) {
        pin->write(0);
        pin->flush();
    }
    hwlib::wait_ms(100);

    uint64_t seed = 99371;

    while(!flagButton.read()) {
        seed--;
        flagButton.refresh();
    }

    srand(seed);
    fieldNum = rand() % 5;
};

void minesweeper::flagCheck() {
    flagButton.refresh();
    if(flagButton.read() != lastFlagButtonState) {
        if(flagButton.read()) {
            flagMode = !flagMode;
        }
    }
    lastFlagButtonState = flagButton.read();
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
                if(field[fieldNum][Xcoord-1][Ycoord-1] == -2) {
                    hwlib::cout << "hier ging het fout denk ik" << hwlib::endl;
                }

                if((field[fieldNum][Xcoord-1][Ycoord-1] == -1) && (ledState[Xcoord-1][Ycoord-1] != -1)) {
                    ledState[Xcoord-1][Ycoord-1] = field[fieldNum][Xcoord-1][Ycoord-1];
                    if((Xcoord >= 0 && Ycoord-1 >= 0) && (Xcoord <= 8 && Ycoord-1 <= 8)) {
                        minesweeper::changeLedState(Xcoord, Ycoord-1);
                    }
                    if((Xcoord >= 0 && Ycoord+1 >= 0) && (Xcoord <= 8 && Ycoord+1 <= 8)) {
                        minesweeper::changeLedState(Xcoord, Ycoord+1);
                    }
                    if((Xcoord-1 >= 0 && Ycoord-1 >= 0) && (Xcoord-1 <= 8 && Ycoord-1 <= 8)) {
                        minesweeper::changeLedState(Xcoord-1, Ycoord-1);
                    }
                    if((Xcoord+1 >= 0 && Ycoord-1 >= 0) && (Xcoord+1 <= 8 && Ycoord-1 <= 8)) {
                        minesweeper::changeLedState(Xcoord+1, Ycoord-1);
                    }
                    if((Xcoord+1 >= 0 && Ycoord+1 >= 0) && (Xcoord+1 <= 8 && Ycoord+1 <= 8)) {
                        minesweeper::changeLedState(Xcoord+1, Ycoord+1);
                    }
                    if((Xcoord-1 >= 0 && Ycoord+1 >= 0) && (Xcoord-1 <= 8 && Ycoord+1 <= 8)) {
                        minesweeper::changeLedState(Xcoord-1, Ycoord+1);
                    }
                    if((Xcoord-1 >= 0 && Ycoord >= 0) && (Xcoord-1 <= 8 && Ycoord <= 8)) {
                        minesweeper::changeLedState(Xcoord-1, Ycoord);
                    }
                    if((Xcoord+1 >= 0 && Ycoord >= 0) && (Xcoord+1 <= 8 && Ycoord <= 8)) {
                        minesweeper::changeLedState(Xcoord+1, Ycoord);
                    }
                } else {
                    ledState[Xcoord-1][Ycoord-1] = field[fieldNum][Xcoord-1][Ycoord-1];
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

void minesweeper::completeCheck() {
    complete = true;
    for(auto set : ledState) {
        for(int item : set) {
            if(item == 9) {
                complete = false;
            }
        }
    }
};

void minesweeper::completeEnd() {
    
    gameGrid.changeLedRGB(1, 1, 0, 0, 0);
    gameGrid.changeLedRGB(2, 1, 0, 0, 0);
    gameGrid.changeLedRGB(3, 1, 255, 255, 0);
    gameGrid.changeLedRGB(4, 1, 255, 255, 0);
    gameGrid.changeLedRGB(5, 1, 255, 255, 0);
    gameGrid.changeLedRGB(6, 1, 255, 255, 0);
    gameGrid.changeLedRGB(7, 1, 0, 0, 0);
    gameGrid.changeLedRGB(8, 1, 0, 0, 0);

    gameGrid.changeLedRGB(1, 2, 0, 0, 0);
    gameGrid.changeLedRGB(2, 2, 0, 0, 0);
    gameGrid.changeLedRGB(3, 2, 255, 255, 0);
    gameGrid.changeLedRGB(4, 2, 255, 255, 0);
    gameGrid.changeLedRGB(5, 2, 255, 255, 0);
    gameGrid.changeLedRGB(6, 2, 255, 255, 0);
    gameGrid.changeLedRGB(7, 2, 0, 0, 0);
    gameGrid.changeLedRGB(8, 2, 0, 0, 0);

    gameGrid.changeLedRGB(1, 3, 255, 255, 0);
    gameGrid.changeLedRGB(2, 3, 255, 255, 0);
    gameGrid.changeLedRGB(3, 3, 255, 255, 0);
    gameGrid.changeLedRGB(4, 3, 255, 255, 0);
    gameGrid.changeLedRGB(5, 3, 255, 255, 0);
    gameGrid.changeLedRGB(6, 3, 255, 255, 0);
    gameGrid.changeLedRGB(7, 3, 255, 255, 0);
    gameGrid.changeLedRGB(8, 3, 255, 255, 0);

    gameGrid.changeLedRGB(1, 4, 255, 255, 0);
    gameGrid.changeLedRGB(2, 4, 0, 0, 0);
    gameGrid.changeLedRGB(3, 4, 255, 255, 0);
    gameGrid.changeLedRGB(4, 4, 255, 255, 0);
    gameGrid.changeLedRGB(5, 4, 255, 255, 0);
    gameGrid.changeLedRGB(6, 4, 255, 255, 0);
    gameGrid.changeLedRGB(7, 4, 0, 0, 0);
    gameGrid.changeLedRGB(8, 4, 255, 255, 0);

    gameGrid.changeLedRGB(1, 5, 255, 255, 0);
    gameGrid.changeLedRGB(2, 5, 255, 255, 0);
    gameGrid.changeLedRGB(3, 5, 255, 255, 0);
    gameGrid.changeLedRGB(4, 5, 255, 255, 0);
    gameGrid.changeLedRGB(5, 5, 255, 255, 0);
    gameGrid.changeLedRGB(6, 5, 255, 255, 0);
    gameGrid.changeLedRGB(7, 5, 255, 255, 0);
    gameGrid.changeLedRGB(8, 5, 255, 255, 0);

    gameGrid.changeLedRGB(1, 6, 0, 0, 0);
    gameGrid.changeLedRGB(2, 6, 0, 0, 0);
    gameGrid.changeLedRGB(3, 6, 255, 255, 0);
    gameGrid.changeLedRGB(4, 6, 255, 255, 0);
    gameGrid.changeLedRGB(5, 6, 255, 255, 0);
    gameGrid.changeLedRGB(6, 6, 255, 255, 0);
    gameGrid.changeLedRGB(7, 6, 0, 0, 0);
    gameGrid.changeLedRGB(8, 6, 0, 0, 0);

    gameGrid.changeLedRGB(2, 7, 0, 0, 0);
    gameGrid.changeLedRGB(3, 7, 0, 0, 0);
    gameGrid.changeLedRGB(1, 7, 0, 0, 0);
    gameGrid.changeLedRGB(4, 7, 255, 255, 0);
    gameGrid.changeLedRGB(5, 7, 255, 255, 0);
    gameGrid.changeLedRGB(6, 7, 0, 0, 0);
    gameGrid.changeLedRGB(7, 7, 0, 0, 0);
    gameGrid.changeLedRGB(8, 7, 0, 0, 0);

    gameGrid.changeLedRGB(1, 8, 0, 0, 0);
    gameGrid.changeLedRGB(2, 8, 0, 0, 0);
    gameGrid.changeLedRGB(3, 8, 255, 255, 0);
    gameGrid.changeLedRGB(4, 8, 255, 255, 0);
    gameGrid.changeLedRGB(5, 8, 255, 255, 0);
    gameGrid.changeLedRGB(6, 8, 255, 255, 0);
    gameGrid.changeLedRGB(7, 8, 0, 0, 0);
    gameGrid.changeLedRGB(8, 8, 0, 0, 0);

    gameGrid.write();
};

void minesweeper::gameOver() {

    gameGrid.changeLedRGB(1, 1, 255, 0, 0);
    gameGrid.changeLedRGB(2, 1, 255, 0, 0);
    gameGrid.changeLedRGB(3, 1, 0, 0, 0);
    gameGrid.changeLedRGB(4, 1, 0, 0, 0);
    gameGrid.changeLedRGB(5, 1, 0, 0, 0);
    gameGrid.changeLedRGB(6, 1, 0, 0, 0);
    gameGrid.changeLedRGB(7, 1, 255, 0, 0);
    gameGrid.changeLedRGB(8, 1, 255, 0, 0);

    gameGrid.changeLedRGB(1, 2, 255, 0, 0);
    gameGrid.changeLedRGB(2, 2, 255, 0, 0);
    gameGrid.changeLedRGB(3, 2, 255, 0, 0);
    gameGrid.changeLedRGB(4, 2, 0, 0, 0);
    gameGrid.changeLedRGB(5, 2, 0, 0, 0);
    gameGrid.changeLedRGB(6, 2, 255, 0, 0);
    gameGrid.changeLedRGB(7, 2, 255, 0, 0);
    gameGrid.changeLedRGB(8, 2, 255, 0, 0);

    gameGrid.changeLedRGB(1, 3, 0, 0, 0);
    gameGrid.changeLedRGB(2, 3, 255, 0, 0);
    gameGrid.changeLedRGB(3, 3, 255, 0, 0);
    gameGrid.changeLedRGB(4, 3, 255, 0, 0);
    gameGrid.changeLedRGB(5, 3, 255, 0, 0);
    gameGrid.changeLedRGB(6, 3, 255, 0, 0);
    gameGrid.changeLedRGB(7, 3, 255, 0, 0);
    gameGrid.changeLedRGB(8, 3, 0, 0, 0);

    gameGrid.changeLedRGB(1, 4, 0, 0, 0);
    gameGrid.changeLedRGB(2, 4, 0, 0, 0);
    gameGrid.changeLedRGB(3, 4, 255, 0, 0);
    gameGrid.changeLedRGB(4, 4, 255, 0, 0);
    gameGrid.changeLedRGB(5, 4, 255, 0, 0);
    gameGrid.changeLedRGB(6, 4, 255, 0, 0);
    gameGrid.changeLedRGB(7, 4, 0, 0, 0);
    gameGrid.changeLedRGB(8, 4, 0, 0, 0);

    gameGrid.changeLedRGB(1, 5, 0, 0, 0);
    gameGrid.changeLedRGB(2, 5, 0, 0, 0);
    gameGrid.changeLedRGB(3, 5, 255, 0, 0);
    gameGrid.changeLedRGB(4, 5, 255, 0, 0);
    gameGrid.changeLedRGB(5, 5, 255, 0, 0);
    gameGrid.changeLedRGB(6, 5, 255, 0, 0);
    gameGrid.changeLedRGB(7, 5, 0, 0, 0);
    gameGrid.changeLedRGB(8, 5, 0, 0, 0);

    gameGrid.changeLedRGB(1, 6, 0, 0, 0);
    gameGrid.changeLedRGB(2, 6, 255, 0, 0);
    gameGrid.changeLedRGB(3, 6, 255, 0, 0);
    gameGrid.changeLedRGB(4, 6, 255, 0, 0);
    gameGrid.changeLedRGB(5, 6, 255, 0, 0);
    gameGrid.changeLedRGB(6, 6, 255, 0, 0);
    gameGrid.changeLedRGB(7, 6, 255, 0, 0);
    gameGrid.changeLedRGB(8, 6, 0, 0, 0);

    gameGrid.changeLedRGB(1, 7, 255, 0, 0);
    gameGrid.changeLedRGB(2, 7, 255, 0, 0);
    gameGrid.changeLedRGB(3, 7, 255, 0, 0);
    gameGrid.changeLedRGB(4, 7, 0, 0, 0);
    gameGrid.changeLedRGB(5, 7, 0, 0, 0);
    gameGrid.changeLedRGB(6, 7, 255, 0, 0);
    gameGrid.changeLedRGB(7, 7, 255, 0, 0);
    gameGrid.changeLedRGB(8, 7, 255, 0, 0);

    gameGrid.changeLedRGB(1, 8, 255, 0, 0);
    gameGrid.changeLedRGB(2, 8, 255, 0, 0);
    gameGrid.changeLedRGB(3, 8, 0, 0, 0);
    gameGrid.changeLedRGB(4, 8, 0, 0, 0);
    gameGrid.changeLedRGB(5, 8, 0, 0, 0);
    gameGrid.changeLedRGB(6, 8, 0, 0, 0);
    gameGrid.changeLedRGB(7, 8, 255, 0, 0);
    gameGrid.changeLedRGB(8, 8, 255, 0, 0);

    gameGrid.write();    
};

void minesweeper::gameLoop() {
    
    while(!bombHit && !complete) {
        lastCoords = coords;
        minesweeper::flagCheck();
        flagLed.write(flagMode);
        flagLed.flush();
        buttonCheck(columnList, rowList, coords);
        minesweeper::changeLedState(coords[0], coords[1]);
        minesweeper::updateField();
        completeCheck();
        hwlib::wait_ms(50);
    };

    if(complete) {
        minesweeper::completeEnd();
    }

    if(bombHit) {
        minesweeper::gameOver();
    }
    
};