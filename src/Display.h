#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <SDL2/SDL.h>

class Display {
   public:
    Display();
    ~Display();
    bool processEvents(bool* keys);
    void refreshDisplay(void* const screen);

   private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
};

#endif