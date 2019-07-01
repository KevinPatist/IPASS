#ifndef LEDS_HPP
#define LEDS_HPP

#include "hwlib.hpp"

//======================== singleLed class =================================

class singleLed {
template<int arrayXamount, int arrayYamount>
friend class ledGrid;
friend class ledStrip;
protected:
    std::array<bool, 24> colorBytes;

public:
    singleLed(uint8_t green = 0, uint8_t red = 0, uint8_t blue = 0)
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

    void changeColor(int green, int red, int blue);
};

//======================== ledStrip class =================================

class ledStrip{
private:
    std::array<singleLed, 100> ledSet;
    int ledAmount = 0;
    due::pin_out dataPin;

public:
    ledStrip(int amount, due::pins pin):
        ledAmount( amount ),
        dataPin( due::pin_out(pin) )
    {
        for(int pos = 0; pos < ledAmount; pos++) {
            ledSet[pos] = singleLed();
        }
    }

    void initialise();

    void writeOne();

    void writeZero();

    void write();

    void changeLedRGB(int ledNum, int red, int green, int blue);

    void changeLedRGB(int ledNum, hwlib::color color);
    
    void colorTest8Leds();
};

//======================== ledGrid class =================================
template<int arrayXamount, int arrayYamount>
class ledGrid{
private:
    std::array< std::array<singleLed, arrayYamount> , arrayXamount> ledSet;
    int ledAmountX = 0;
    int ledAmountY = 0;
    due::pin_out dataPin;

public:
    ledGrid(int amountX, int amountY, arrayXamount, arrayYamount, due::pins pin):
        ledAmountX( amountX ),
        ledAmountY( amountY ),
        dataPin( due::pin_out(pin) )
    {
        for(int posX = 0; posX < ledAmountX; posX++) {
            for(int posY = 0; posY < ledAmountY; posY++) {
                ledSet[posX][posY] = singleLed();
            }
        }
    }

    void initialise();

    void writeOne();

    void writeZero();

    void write();

    void changeLedRGB(int ledNumX, int ledNumY, int red, int green, int blue);

    void changeLedRGB(hwlib::xy, hwlib::color color);
    
};

#endif // LEDS_HPP