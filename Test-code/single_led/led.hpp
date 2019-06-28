#ifndef LED_HPP
#define LED_HPP

#include <hwlib.hpp>

class led {
    private:
        bool color[24] = {};
        hwlib::pin_out & ledPin;

    public:
        led(int green, int red, int blue, hwlib::pin_out & pin):
            ledPin( pin )
        {
            int temp = 0;
            int position = 0;
            bool check = false;
            for(int kleur : {green, red, blue}) {
                temp = kleur;
                for(int test = 128; test >= 1; test /= 2 ) {
                    check = (temp - test) >= 0;
                    color[position] = check;
                    if( check ) {
                        temp -= test;
                    };
                    position++;
                }
            }
        }

        void singleWrite();
        
};

#endif //LED_HPP