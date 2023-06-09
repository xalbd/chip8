#include "Display.h"

#include <SDL2/SDL.h>

#include <iostream>

Display::Display() {
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not be initialized. Error: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow("Chip-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cout << "Window could not be created. Error: " << SDL_GetError() << std::endl;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Event e;
            bool quit = false;
            while (quit == false) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) quit = true;
                }
            }

            SDL_DestroyWindow(window);

            // Quit SDL subsystems
            SDL_Quit();
        }
    }
}

Display::~Display() {}
