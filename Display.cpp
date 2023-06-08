#include "Display.h"

#include <bitset>
#include <iostream>

Display::Display() {}

Display::~Display() {}

void Display::printStd() {
    for (auto line : screen) {
        std::cout << std::bitset<64>(line) << std::endl;
    }
}

void Display::clear() {
    for (auto& line : screen) {
        line = 0;
    }
}

bool Display::toggle(u_int8_t x, u_int8_t y) {
    u_int64_t mask = 1;
    bool toggled = screen[y] & mask << (63 - y);
    screen[x] ^= mask << (63 - y);
    return toggled;
}