#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <SDL2/SDL.h>

const int DISPLAY_HEIGHT = 320;
const int DISPLAY_WIDTH = 640;

class Display {
   public:
    Display();
    ~Display();

   private:
    SDL_Window* window;
};

#endif