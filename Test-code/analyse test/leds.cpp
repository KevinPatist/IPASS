#include "leds.hpp"

//THIS FUNCTION IS MADE BY WOUTER VAN OOIJEN REPOSITORY WOVO/GODAFOSS
static void __attribute__((noinline)) wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
};

void leds::initLed() {
    dataPin.write(0);
    dataPin.flush();
    hwlib::wait_ms(1);
};

void leds::writeOne() {
    dataPin.write(1);
    dataPin.flush();
    wait_busy(50);              
    dataPin.write(0);
    dataPin.flush();
    wait_busy(8);
};

void leds::writeZero() {
    dataPin.write(1);
    dataPin.flush();
    wait_busy(16);              
    dataPin.write(0);
    dataPin.flush();
    wait_busy(35);
};

void leds::write() {
    for(bool bit : colorBytes) {
        if(bit) {
            leds::writeOne();
        } else {
            leds::writeZero();
        }
    };
};
