#include "functie.hpp"

int main() {
    auto off = hwlib::color(0,0,0);
    auto white = hwlib::color(255,255,255);
    auto yellow = hwlib::color(255,255,0);
    auto orange = hwlib::color(255,127,0);
    auto red = hwlib::color(255,0,0);
    auto green = hwlib::color(0,255,0);
    auto blue = hwlib::color(0,0,255);

    auto grid = ledGrid(2, 4, hwlib::target::pins::d5);
    grid.initialise();

    hwlib::wait_ms(100);
    std::array<int, 2> coords = {0,0};
    std::array<hwlib::target::pin_in *, 1> rowList;
    auto row1 = hwlib::target::pin_in(hwlib::target::pins::d13);
    rowList[0] = &row1;

    std::array<hwlib::target::pin_out *, 4> columnList;
    auto c1 = hwlib::target::pin_out(hwlib::target::pins::d9);
    auto c2 = hwlib::target::pin_out(hwlib::target::pins::d8);
    auto c3 = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto c4 = hwlib::target::pin_out(hwlib::target::pins::d6);
    columnList[0] = &c1;
    columnList[1] = &c2; 
    columnList[2] = &c3; 
    columnList[3] = &c4; 
    columnList[0]->write(0);
    columnList[1]->write(0);
    columnList[2]->write(0);
    columnList[3]->write(0);
    columnList[0]->flush();
    columnList[1]->flush();
    columnList[2]->flush();
    columnList[3]->flush();
    hwlib::wait_ms(500);
    
    while(1) {
        buttonCheck(columnList, rowList, coords);
        hwlib::cout << "started" << hwlib::endl;
        hwlib::cout << hwlib::setw(8) << "row:" << hwlib::setw(5) << hwlib::right << coords[1] << hwlib::endl;
        hwlib::cout << hwlib::setw(8) << "column:" << hwlib::setw(5) << hwlib::right << coords[0] << hwlib::endl;
        hwlib::cout << hwlib::endl;
        hwlib::wait_ms(500);
    }
}