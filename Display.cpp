#include "Display.h"

#include <bitset>
#include <iostream>

Display::Display() {}

Display::~Display() {}

void Display::printStd() {
    for (auto& line : screen) {
        std::cout << std::bitset<64>(line).to_string('.', 'x') << std::endl;
    }
    std::cout << std::endl;
}

void Display::clear() {
    for (auto& line : screen) {
        line = 0;
    }
}

bool Display::toggle(u_int8_t row, u_int8_t col) {
    col %= SCREEN_WIDTH;
    row %= SCREEN_HEIGHT;

    uint64_t mask = 1;
    mask <<= (SCREEN_WIDTH - 1 - col);

    bool toggled = screen[row] & mask;
    screen[row] ^= mask;
    return toggled;
}