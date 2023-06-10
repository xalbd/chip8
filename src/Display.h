#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <SDL2/SDL.h>

#include <cstdint>
#include <unordered_map>

const int TEXTURE_HEIGHT = 32;
const int TEXTURE_WIDTH = 64;
const int DISPLAY_SCALING = 10;
const std::unordered_map<SDL_Keycode, uint8_t> keymap = {
    {SDL_KeyCode::SDLK_1, 0x1}, {SDL_KeyCode::SDLK_2, 0x2}, {SDL_KeyCode::SDLK_3, 0x3},
    {SDL_KeyCode::SDLK_q, 0x4}, {SDL_KeyCode::SDLK_w, 0x5}, {SDL_KeyCode::SDLK_e, 0x6},
    {SDL_KeyCode::SDLK_a, 0x7}, {SDL_KeyCode::SDLK_s, 0x8}, {SDL_KeyCode::SDLK_d, 0x9},
    {SDL_KeyCode::SDLK_x, 0x0}, {SDL_KeyCode::SDLK_z, 0xA}, {SDL_KeyCode::SDLK_c, 0xB},
    {SDL_KeyCode::SDLK_4, 0xC}, {SDL_KeyCode::SDLK_r, 0xD}, {SDL_KeyCode::SDLK_f, 0xE},
    {SDL_KeyCode::SDLK_v, 0xF},
};

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