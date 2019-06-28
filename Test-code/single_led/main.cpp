#include "led.hpp"

// //THIS FUNCTION IS MADE BY WOUTER VAN OOIJEN REPOSITORY WOVO/GODAFOSS
// static void __attribute__((noinline)) wait_busy( int32_t n ){
//    __asm volatile(                  
//       "   .align 4           \t\n"  
//       "1: subs.w  r0, #3     \t\n"  
//       "   bgt 1b             \t\n"  
//       : : "r" ( n )          // uses (reads) n         
//    ); 
// };

int main() {
    hwlib::wait_ms(0);
    auto ledpin = hwlib::target::pin_out(hwlib::target::pins::d6);
    auto ledje = led(0, 255, 255, ledpin);
    for(;;) {
        ledje.singleWrite();
        hwlib::wait_us(50);
    }
};
