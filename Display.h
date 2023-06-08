#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <cstdint>

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;

class Display {
   public:
    Display();
    ~Display();
    void printStd();
    void clear();
    bool toggle(u_int8_t row, u_int8_t col);

   private:
    uint64_t screen[SCREEN_HEIGHT] = {};
};

#endif