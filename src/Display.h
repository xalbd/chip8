#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <SDL2/SDL.h>

class Display {
   public:
    Display();
    ~Display();
    void processEvents(bool* keys, bool& running);
    void refreshDisplay(void* const screen);

   private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;
};

#endif