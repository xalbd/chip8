#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <cstdint>

class Display {
   public:
    Display();
    ~Display();
    void printStd();
    void clear();
    bool toggle(u_int8_t x, u_int8_t y);

   private:
    uint64_t screen[32] = {};
};

#endif