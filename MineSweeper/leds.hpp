#ifndef LEDS_HPP
#define LEDS_HPP

#include "hwlib.hpp"

/// @file

//======================== singleLed class =================================

/// class used to hold the colordata of a single RGB LED
///
/// This class is used in ledGrid and ledStrip to keep the color data of each led easy to acces
class singleLed {
friend class ledGrid;
friend class ledStrip;
protected:
    std::array<bool, 24> colorBytes;

public:
    /// construct a singleLed object to store the colordata of an RGB LED
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

    /// A function to change the data in the array
    ///
    /// This function is meant to be used by ledStrip and ledGrid to change the color of their LEDs
    void changeColor(int green, int red, int blue);
};

//======================== ledStrip class =================================

/// A class to control a maximum of 250 RGB LEDs on a single strip.
///
/// Each LED can be individually controlled
class ledStrip{
private:
    std::array<singleLed, 250> ledSet;
    int ledAmount = 0;
    due::pin_out dataPin;

public:
    /// contstruct a ledStrip object with a given amount of LEDs
    /// 
    /// The amount of LEDs is limited to 250
    ledStrip(int amount, due::pins pin):
        ledAmount( amount ),
        dataPin( due::pin_out(pin) )
    {
        for(int pos = 0; pos < ledAmount; pos++) {
            ledSet[pos] = singleLed();
        }
    }

    /// Setting the datapin to low and waiting a millisecond so there's no power surge that can be mistaken for a bit. 
    void initialise();

    /// Writing a "one" bit to the datapin by setting the power high and low with the right timing
    void writeOne();

    /// Writing a "zero" bit to the datapin by setting the power high and low with the right timing
    void writeZero();

    /// using the writeZero and writeOne functions to write the strips color data to the datapin
    void write();

    /// A funtion to set an individual LEDs color data using three integers for the red, green and blue values 
    void changeLedRGB(int ledNum, int red, int green, int blue);

    /// A function to set an individual LEDs color data using hwlib::color 
    void changeLedRGB(int ledNum, hwlib::color color);
    
    /// A function to make a little rainbow-ish thing show up on a ledstrip with 8 LEDs
    /// 
    /// this function is meant to test a short ledstrip 
    void colorTest8Leds();
};

//======================== ledGrid class =================================

/// A class to control a grid of RGB LEDs
/// 
/// Each LED in the grid can be individually controlled using it's coordinates
class ledGrid{
private:
    std::array< std::array<singleLed, 100> , 100> ledSet;
    int ledAmountX = 0;
    int ledAmountY = 0;
    due::pin_out dataPin;

public:
    /// construct a ledGrid object with given width and height
    ledGrid(int amountX, int amountY, due::pins pin):
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


    /// Setting the datapin to low and waiting a millisecond so there's no power surge that can be mistaken for a bit. 
    void initialise();

    /// Writing a "one" bit to the datapin by setting the power high and low with the right timing
    void writeOne();

    /// Writing a "zero" bit to the datapin by setting the power high and low with the right timing
    void writeZero();

    /// using the writeZero and writeOne functions to write the strips color data to the datapin
    void write();

    /// A funtion to set an individual LEDs color data using two integers for the x and y coordinates and three integers for the red, green and blue values     
    void changeLedRGB(int ledNumX, int ledNumY, int red, int green, int blue);

    /// A function to set an individual LEDs color using hwlib::color and hwlib::xy for the location
    void changeLedRGB(hwlib::xy, hwlib::color color);
    
};

#endif // LEDS_HPP