#include "Chip8.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Display.h"

Chip8::Chip8(std::string romFile) {
    loadROM(romFile);
    display = new Display();
}

Chip8::~Chip8() { delete display; }

void Chip8::run() {
    int delayTimerTicks = 0, soundTimerTicks = 0;

    auto time = std::chrono::high_resolution_clock::now();
    auto now = time;
    const auto tickdiff = std::chrono::microseconds(CYCLE_LEN_MICROSECONDS);

    while (display->processEvents(keys)) {
        now = std::chrono::high_resolution_clock::now();
        if (now - time >= tickdiff) {
            time = now;

            if (delayTimerTicks == 0 && delayTimer != 0) {
                delayTimer--;
                delayTimerTicks = TIMER_TICKS;
            } else if (delayTimerTicks > 0) {
                delayTimerTicks--;
            }

            if (soundTimerTicks == 0 && soundTimer != 0) {
                soundTimer--;
                soundTimerTicks = TIMER_TICKS;
            } else if (soundTimerTicks > 0) {
                soundTimerTicks--;
            }

            cycle();
        }
    }
}

void Chip8::loadROM(std::string romFile) {
    // load font sprite data into interpreter section of ram
    for (int i = 0; i < FONT_MEMSIZE; i++) {
        ram[FONT_START_ADDRESS + i] = FONT[i];
    }

    // load rom data
    std::ifstream file(romFile, std::ios::binary | std::ios::ate);
    if (file.is_open()) {
        int rom_size = file.tellg();
        char* rom = new char[rom_size];

        file.seekg(0, std::ios::beg);
        file.read(rom, rom_size);
        file.close();

        for (int i = 0; i < rom_size; i++) {
            ram[START_ADDRESS + i] = rom[i];
        }

        delete[] rom;
    }

    // set program counter to start execution at program space
    pc = START_ADDRESS;
}

void Chip8::cycle() {
    // read opcode
    opcode = (ram[pc] << 8) + ram[pc + 1];
    pc += 2;

    // interpret
    parseInstruction();
    runInstruction();

    // update
    display->refreshDisplay(screen);
}

void Chip8::parseInstruction() {
    x = (opcode & 0xF00) >> 8;
    y = (opcode & 0xF0) >> 4;
    imm = opcode & 0xFF;
    addr = opcode & 0xFFF;
}

bool Chip8::toggle(u_int8_t row, u_int8_t col) {
    col %= SCREEN_WIDTH;
    row %= SCREEN_HEIGHT;

    screen[row * SCREEN_WIDTH + col] = ~screen[row * SCREEN_WIDTH + col];
    return screen[row * SCREEN_WIDTH + col] == 0;
}
