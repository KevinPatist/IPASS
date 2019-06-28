#include "hwlib.hpp"
#include "leds.hpp"
#include "buttonGrid.hpp"

template<unsigned int N, unsigned int M>
void ledButtonRefresh(std::array<hwlib::target::pin_out *, N> &columnList, 
                      std::array<hwlib::target::pin_in *, M> &rowList,
                      std::array<std::array<bool, M>, N> &ledState,
                      std::array<int, 2> &coords, std::array<int, 2> &lastCoords, 
                      ledGrid &grid) {

    lastCoords = coords;
    buttonCheck(columnList, rowList, coords);

    if(coords[0] > 0) {
        if(ledState[coords[0]-1][coords[1]-1] && (coords != lastCoords)) {
            grid.changeLedRGB(coords[0], coords[1], 0, 0, 0);
            grid.write();
            ledState[coords[0]-1][coords[1]-1] = false;
        } else if(!ledState[coords[0]-1][coords[1]-1] && (coords != lastCoords)){
            grid.changeLedRGB(coords[0], coords[1], 255, 255, 255);
            grid.write();
            ledState[coords[0]-1][coords[1]-1] = true;
        }
    }
    hwlib::wait_ms(50);
}