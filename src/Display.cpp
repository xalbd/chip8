#include "Display.h"

#include <SDL2/SDL.h>

#include "Constants.h"

Display::Display() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Chip-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH * DISPLAY_SCALING, SCREEN_HEIGHT * DISPLAY_SCALING,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_ShowWindow(window);
}

Display::~Display() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::refreshDisplay(void* const screen) {
    int pitch = 4 * SCREEN_WIDTH;  // accounts for RGBA channels
    SDL_UpdateTexture(texture, NULL, screen, pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Display::processEvents(bool* keys, bool& running) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    keys[0x1] = true;
                    break;
                case SDLK_2:
                    keys[0x2] = true;
                    break;
                case SDLK_3:
                    keys[0x3] = true;
                    break;
                case SDLK_q:
                    keys[0x4] = true;
                    break;
                case SDLK_w:
                    keys[0x5] = true;
                    break;
                case SDLK_e:
                    keys[0x6] = true;
                    break;
                case SDLK_a:
                    keys[0x7] = true;
                    break;
                case SDLK_s:
                    keys[0x8] = true;
                    break;
                case SDLK_d:
                    keys[0x9] = true;
                    break;
                case SDLK_x:
                    keys[0x0] = true;
                    break;
                case SDLK_z:
                    keys[0xA] = true;
                    break;
                case SDLK_c:
                    keys[0xB] = true;
                    break;
                case SDLK_4:
                    keys[0xC] = true;
                    break;
                case SDLK_r:
                    keys[0xD] = true;
                    break;
                case SDLK_f:
                    keys[0xE] = true;
                    break;
                case SDLK_v:
                    keys[0xF] = true;
                    break;
                case SDLK_ESCAPE:
                    running = false;
                    break;
            }
        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_1:
                    keys[0x1] = false;
                    break;
                case SDLK_2:
                    keys[0x2] = false;
                    break;
                case SDLK_3:
                    keys[0x3] = false;
                    break;
                case SDLK_q:
                    keys[0x4] = false;
                    break;
                case SDLK_w:
                    keys[0x5] = false;
                    break;
                case SDLK_e:
                    keys[0x6] = false;
                    break;
                case SDLK_a:
                    keys[0x7] = false;
                    break;
                case SDLK_s:
                    keys[0x8] = false;
                    break;
                case SDLK_d:
                    keys[0x9] = false;
                    break;
                case SDLK_x:
                    keys[0x0] = false;
                    break;
                case SDLK_z:
                    keys[0xA] = false;
                    break;
                case SDLK_c:
                    keys[0xB] = false;
                    break;
                case SDLK_4:
                    keys[0xC] = false;
                    break;
                case SDLK_r:
                    keys[0xD] = false;
                    break;
                case SDLK_f:
                    keys[0xE] = false;
                    break;
                case SDLK_v:
                    keys[0xF] = false;
                    break;
            }
        }
    }
}
