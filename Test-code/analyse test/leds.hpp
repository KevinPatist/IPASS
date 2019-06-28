#ifndef LEDS_HPP
#define LEDS_HPP

#include "hwlib.hpp"

class leds {
private:
    std::array<bool, 24> colorBytes;
    due::pin_out dataPin;

public:
    leds(uint8_t green, uint8_t red, uint8_t blue, due::pins pin):
        dataPin( due::pin_out(pin) )
    {
        int temp = 0;
        int position = 0;
        bool check = false;
        for(int kleur : {green, red, blue}) {
            temp = kleur;
            for(int test = 128; test >= 1; test /= 2 ) {
                check = (temp - test) >= 0;
                colorBytes[position] = check;
                if( check ) {
                    temp -= test;
                };
                position++;
            }
        }
    }

    void initLed();

    void writeOne();

    void writeZero();

    void write();
};

#endif // LEDS_HPP