#include "hwlib.hpp"    

int main() {
    auto row1 = hwlib::target::pin_in(hwlib::target::pins::d12);
    row1.pullup_disable();
    auto column1 = hwlib::target::pin_out(hwlib::target::pins::d9);
    bool buttonState = 0;

    column1.write(1);
    column1.flush();

    while(1) {
        row1.refresh();
        buttonState = row1.read();

        hwlib::cout << hwlib::setw(13) << "buttonState: " << buttonState << hwlib::endl;
        hwlib::wait_ms(200);

    }
}