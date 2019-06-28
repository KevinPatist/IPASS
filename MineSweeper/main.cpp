#include "ledAndButtons.hpp"

int main() {

    auto grid = ledGrid(8, 8, hwlib::target::pins::d5);
    grid.initialise();

    std::array<std::array<bool, 8>, 8> ledState = {{{false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, 
                                                    {false,false,false,false,false,false,false,false}, }};

    hwlib::wait_ms(100);
    std::array<int, 2> coords = {0,0};
    std::array<int, 2> lastCoords = {0,0};
    std::array<hwlib::target::pin_in *, 8> rowList;
    auto row1 = hwlib::target::pin_in(hwlib::target::pins::d6);
    auto row2 = hwlib::target::pin_in(hwlib::target::pins::d7);
    auto row3 = hwlib::target::pin_in(hwlib::target::pins::d8);
    auto row4 = hwlib::target::pin_in(hwlib::target::pins::d9);
    auto row5 = hwlib::target::pin_in(hwlib::target::pins::d10);
    auto row6 = hwlib::target::pin_in(hwlib::target::pins::d11);
    auto row7 = hwlib::target::pin_in(hwlib::target::pins::d12);
    auto row8 = hwlib::target::pin_in(hwlib::target::pins::d13);
    rowList[0] = &row1;
    rowList[1] = &row2;
    rowList[2] = &row3;
    rowList[3] = &row4;
    rowList[4] = &row5;
    rowList[5] = &row6;
    rowList[6] = &row7;
    rowList[7] = &row8;

    std::array<hwlib::target::pin_out *, 8> columnList;
    auto c1 = hwlib::target::pin_out(hwlib::target::pins::d22);
    auto c2 = hwlib::target::pin_out(hwlib::target::pins::d23);
    auto c3 = hwlib::target::pin_out(hwlib::target::pins::d24);
    auto c4 = hwlib::target::pin_out(hwlib::target::pins::d25);
    auto c5 = hwlib::target::pin_out(hwlib::target::pins::d26);
    auto c6 = hwlib::target::pin_out(hwlib::target::pins::d27);
    auto c7 = hwlib::target::pin_out(hwlib::target::pins::d28);
    auto c8 = hwlib::target::pin_out(hwlib::target::pins::d29);
    columnList[0] = &c1;
    columnList[1] = &c2; 
    columnList[2] = &c3; 
    columnList[3] = &c4; 
    columnList[4] = &c5;
    columnList[5] = &c6; 
    columnList[6] = &c7; 
    columnList[7] = &c8; 

    for(auto pin : columnList) {
        pin->write(0);
        pin->flush();
    }

    hwlib::wait_ms(500);
    
    while(1) {
        ledButtonRefresh(columnList, rowList, ledState, coords, lastCoords, grid);
    }
}