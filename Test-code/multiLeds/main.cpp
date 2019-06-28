#include "leds.hpp"

int main() {
    auto off = hwlib::color(0,0,0);
    auto white = hwlib::color(255,255,255);
    auto yellow = hwlib::color(255,255,0);
    auto orange = hwlib::color(255,127,0);
    auto red = hwlib::color(255,0,0);
    auto green = hwlib::color(0,255,0);
    auto blue = hwlib::color(0,0,255);
    
    auto grid = ledGrid(4, 2, hwlib::target::pins::d5);
    grid.initialise();
    
    grid.changeLedRGB(3, 1, 0, 255, 0);

    grid.write();
    
};
