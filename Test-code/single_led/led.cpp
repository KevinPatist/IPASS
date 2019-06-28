#include "led.hpp"

//THIS FUNCTION IS MADE BY WOUTER VAN OOIJEN REPOSITORY WOVO/GODAFOSS
static void __attribute__((noinline)) wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
};

void led::singleWrite() {
    for(int i = 0; i < 24; i++) {
        if(color[i]) {
            ledPin.write(1);
            ledPin.flush();
            wait_busy(2);              
            ledPin.write(0);
            ledPin.flush();
            wait_busy(1);
        } else {
            ledPin.write(1);
            ledPin.flush();
            wait_busy(1);              
            ledPin.write(0);
            ledPin.flush();
            wait_busy(2);
        }
    }
};