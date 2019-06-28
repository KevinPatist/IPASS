#include "leds.hpp"

// //THIS FUNCTION IS MADE BY WOUTER VAN OOIJEN REPOSITORY WOVO/GODAFOSS
// static void __attribute__((noinline)) wait_busy( int32_t n ){
//    __asm volatile(                  
//       "   .align 4           \t\n"  
//       "1: subs.w  r0, #3     \t\n"  
//       "   bgt 1b             \t\n"  
//       : : "r" ( n )          // uses (reads) n         
//    ); 
// };

// void writeOne(hwlib::pin_out ledpin) {
//     ledpin.write(1);
//     ledpin.flush();
//     wait_busy(58);              
//     ledpin.write(0);
//     ledpin.flush();
//     wait_busy(12);
// };

// void writeZero(hwlib::pin_out & ledpin) {
//     ledpin.write(1);
//     ledpin.flush();
//     wait_busy(16);              
//     ledpin.write(0);
//     ledpin.flush();
//     wait_busy(50);
// }

int main() {
    auto led = leds(255, 0, 0, hwlib::target::pins::d6);
    led.initLed();
    int derest = 0;
    int colorByteCounter = 0;
    //for(;;) {
        derest = 0;
        colorByteCounter = 0;
        
        for( derest = 0; derest < 144; derest++) {
            led.writeZero();
        }
          
        led.write();

        //write leds off (last 5 leds)
        for( derest = 0; derest < 24; derest++) {
            led.writeZero();
        }
        hwlib::wait_us(50);
    //}
};
