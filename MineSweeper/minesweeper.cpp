#include "minesweeper.hpp"

void minesweeper::gameInit() {
    gameGrid.initialise();
    
    for(auto pin : columnList) {
        pin->write(0);
        pin->flush();
    }
};

void minesweeper::gameLoop() {
    lastCoords = coords;
    buttonCheck(columnList, rowList, coords);

    if(coords[0] > 0) {
        if(flagMode) {
            if((ledState[coords[0]-1][coords[1]-1] == -2) && coords != lastCoords) {
                ledState[coords[0]-1][coords[1]-1] = 9;
            } else if((ledState[coords[0]-1][coords[1]-1] == 9) && coords != lastCoords) {
                ledState[coords[0]-1][coords[1]-1] = -2;
            }
        } else {
            if(ledState[coords[0]-1][coords[1]-1] == 9) {
                ledState[coords[0]-1][coords[1]-1] = field[coords[0]-1][coords[1]-1];
            };
        }

        for(int Ypos = 0; Ypos <8; Ypos++) {
            for(int Xpos = 0; Xpos <8; Xpos++) {
                ledState[Xpos][Ypos]; 
            }
        }
    }
    hwlib::wait_ms(50);
}
};