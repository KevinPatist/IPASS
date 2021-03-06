// ==========================================================================
//
// File      : buttonGrid.hpp
// Part of   : IPASS Minesweeper
// Copyright : kevin.patist@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

#include "hwlib.hpp"

template<unsigned int N>
int rowCheck( std::array<hwlib::target::pin_in *, N> &rowList) {
    bool rowRead = false;
    int rowCount = 0;
    for(unsigned int j=0; j < N; j++) {
        rowCount++;
        rowList[j]->refresh();
        rowRead = rowList[j]->read();
        if(rowRead) {
            return rowCount;
        };
    };
    return 0;
};

template<unsigned int N, unsigned int M>
void buttonCheck(std::array<hwlib::target::pin_out *, N> &columnList, 
                 std::array<hwlib::target::pin_in *, M> &rowList,
                 std::array<int, 2> &coords) {
    coords[0] = 0;
    coords[1] = 0;   
    bool good = false;              
    for(unsigned int i=0; i < N; i++) { 
        columnList[i]->write(1);
        columnList[i]->flush();
        hwlib::wait_ms(10);
        coords[1] = rowCheck(rowList);
        columnList[i]->write(0);
        columnList[i]->flush();
        if(coords[1] > 0) {
            coords[0] = i+1;
            good = true;
            break;
        };
    };  
    if(!good) {
        coords[0] = 0;
    } 
};


