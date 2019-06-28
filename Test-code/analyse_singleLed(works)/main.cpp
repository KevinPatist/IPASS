#include "hwlib.hpp"

//THIS FUNCTION IS MADE BY WOUTER VAN OOIJEN REPOSITORY WOVO/GODAFOSS
static void __attribute__((noinline)) wait_busy( int32_t n ){
   __asm volatile(                  
      "   .align 4           \t\n"  
      "1: subs.w  r0, #3     \t\n"  
      "   bgt 1b             \t\n"  
      : : "r" ( n )          // uses (reads) n         
   ); 
};

int main() {
    auto ledpin = hwlib::target::pin_out(hwlib::target::pins::d6);
    ledpin.write(0);
    ledpin.flush();
    hwlib::wait_ms(1);
    int derest = 0;
    int colorByteCounter = 0;
    //for(;;) {
        derest = 0;
        colorByteCounter = 0;
        
        for( derest = 0; derest < 144; derest++) {
            ledpin.write(1);
            ledpin.flush();
            wait_busy(58);              
            ledpin.write(0);
            ledpin.flush();
            wait_busy(12);
        }

        //write low for 8 bits
        for( colorByteCounter = 0; colorByteCounter < 24; colorByteCounter++) {
            ledpin.write(1);
            ledpin.flush();
            wait_busy(16);              
            ledpin.write(0);
            ledpin.flush();
            wait_busy(50);
        };

        //write leds off (last 5 leds)
        for( derest = 0; derest < 24; derest++) {
            ledpin.write(1);
            ledpin.flush();
            wait_busy(58);              
            ledpin.write(0);
            ledpin.flush();
            wait_busy(12);
        }
        hwlib::wait_us(50);
    //}
};
