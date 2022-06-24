#include "leds.hpp"

// ==========================================================================
//
// File      : leds.cpp
// Part of   : WS2812B_library
// Copyright : kevin.patist@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================

//THIS FUNCTION IS MADE BY WOUTER VAN OOIJEN REPOSITORY WOVO/GODAFOSS
static void __attribute__((noinline)) wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
};

//======================== singleLed class =================================

// This function changed the colordata in a singleLed object
void singleLed::changeColor(int green, int red, int blue) {
    int temp = 0;
    int position = 0;
    bool check = false;
    for(int kleur : {green, red, blue}) {
        temp = kleur;
        for(int test = 128; test >= 1; test /= 2) {
            check = (temp - test) >= 0;
            colorBytes[position] = check;
            if( check ) {
                temp = test;
            };
            position++;
        }
    }
};

//======================== ledStrip class =================================

// This function writes a "one" bit to the datapin
void ledStrip::writeOne() {
    dataPin.write(1);
    dataPin.flush();
    wait_busy(50);              
    dataPin.write(0);
    dataPin.flush();
    wait_busy(14);
};

// This function writes a "zero" bit to the datapin
void ledStrip::writeZero() {
    dataPin.write(1);
    dataPin.flush();
    wait_busy(16);              
    dataPin.write(0);
    dataPin.flush();
    wait_busy(50);
};

// This function wipes the datapin by writing it full of zeros and waiting a while
void ledStrip::initialise() {
    dataPin.write(0);
    dataPin.flush();
    hwlib::wait_ms(1);
};

void ledStrip::write() {
    for(int led = 0; led < ledAmount; led++) {
        for(bool bit : ledSet[led].colorBytes) {
            if(bit) {
                ledStrip::writeOne();
            } else {
                ledStrip::writeZero();
            }
        }
    }
};

void ledStrip::changeLedRGB(int ledNum, int red, int green, int blue) {
    ledSet[ledNum-1].changeColor((green/2),(red/2),(blue/2));  //divided by 2 to set brightness to 50% (don't divide to set full brightness)
};

void ledStrip::changeLedRGB(int ledNum, hwlib::color color) {
    ledSet[ledNum-1].changeColor((color.green/2),(color.red/2),(color.blue/2));  //divided by 2 to set brightness to 50% (don't divide to set full brightness;
}

void ledStrip::colorTest8Leds() {
    for(;;) {
        for(int i = 0; i<8; i++) {
            if(i+1 <=8) {
                ledStrip::changeLedRGB(i+1, 0, 0, 0);
            } else {
                ledStrip::changeLedRGB(i-8+1, 0, 0, 0);
            }
            
            if(i+2 <=8) {
                ledStrip::changeLedRGB(i+2, 255, 255, 255);
            } else {
                ledStrip::changeLedRGB(i-8+2, 255, 255, 255);
            }
            
            if(i+3 <=8) {
                ledStrip::changeLedRGB(i+3, 255, 255, 0);
            } else {
                ledStrip::changeLedRGB(i-8+3, 255, 255, 0);
            }

            if(i+4 <=8) {
                ledStrip::changeLedRGB(i+4, 255, 127, 0);
            } else {
                ledStrip::changeLedRGB(i-8+4, 255, 127, 0);
            }

            if(i+5 <=8) {
                ledStrip::changeLedRGB(i+5, 255, 0, 0);
            } else {
                ledStrip::changeLedRGB(i-8+5, 255, 0, 0);
            }
            
            if(i+6 <=8) {
                ledStrip::changeLedRGB(i+6, 0, 255, 0);
            } else {
                ledStrip::changeLedRGB(i-8+6, 0, 255, 0);
            }
            
            if(i+7 <=8) {
                ledStrip::changeLedRGB(i+7, 0, 0, 255);
            } else {
                ledStrip::changeLedRGB(i-8+7, 0, 0, 255);
            }

            if(i+8 <=8) {
                ledStrip::changeLedRGB(i+8, 255, 255, 255);
            } else {
                ledStrip::changeLedRGB(i, 255, 255, 255);
            }

            ledStrip::write();
            hwlib::wait_ms(250);
        }
    }
};

//======================== ledGrid class =================================

void ledGrid::writeOne() {
    dataPin.write(1);
    dataPin.flush();
    wait_busy(50);              
    dataPin.write(0);
    dataPin.flush();
    wait_busy(14);
};

void ledGrid::writeZero() {
    dataPin.write(1);
    dataPin.flush();
    wait_busy(16);              
    dataPin.write(0);
    dataPin.flush();
    wait_busy(50);
};

void ledGrid::initialise() {
    dataPin.write(0);
    dataPin.flush();
    hwlib::wait_ms(1);
};

void ledGrid::write() {
    for(int ledY = 0; ledY < ledAmountY; ledY++) {
        for(int ledX = 0; ledX < ledAmountX; ledX++) {
            for(bool bit : ledSet[ledX][ledY].colorBytes) {
                if(bit) {
                    ledGrid::writeOne();
                } else {
                    ledGrid::writeZero();
                }
            }
        }
    }
};

void ledGrid::changeLedRGB(int ledNumX, int ledNumY, int red, int green, int blue) {
    ledSet[ledNumX-1][ledNumY-1].changeColor((green/2),(red/2),(blue/2));  //divided by 2 to set brightness to 50% (don't divide to set full brightness)
};

void ledGrid::changeLedRGB(hwlib::xy coordinates, hwlib::color color) {
    ledSet[coordinates.x-1][coordinates.y-1].changeColor((color.green/2),(color.red/2),(color.blue/2));  //divided by 2 to set brightness to 50% (don't divide to set full brightness)
};

