#include "Chip8.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Display.h"

Chip8::Chip8(std::string romFile) { loadROM(romFile); }

Chip8::~Chip8() {}

void Chip8::run() {
    auto time = std::chrono::high_resolution_clock::now();
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        if (now - time > std::chrono::milliseconds(150)) {
            time = now;
            cycle();  // delay
            printStd();
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
    printStatus();
    pc += 2;

    // interpret
    parseInstruction();
    runInstruction();
}

void Chip8::printStatus() {
    using namespace std;
    cout << hex << (int)pc << ": " << (int)opcode << endl << "reg- ";
    for (int i = 0; i < 16; i++) cout << hex << i << ":" << (int)reg[i] << " ";
    cout << endl << hex << "i- " << index << endl << "stack- ";
    for (int i = 0; i < sp; i++) cout << hex << (int)stack[i] << " ";
    cout << endl;
}

void Chip8::parseInstruction() {
    x = (opcode & 0xF00) >> 8;
    y = (opcode & 0xF0) >> 4;
    imm = opcode & 0xFF;
    addr = opcode & 0xFFF;
}

void Chip8::printStd() {
    for (auto& line : screen) {
        std::cout << std::bitset<64>(line).to_string('.', 'x') << std::endl;
    }
    std::cout << std::endl;
}

void Chip8::clear() {
    for (auto& line : screen) {
        line = 0;
    }
}

bool Chip8::toggle(u_int8_t row, u_int8_t col) {
    col %= SCREEN_WIDTH;
    row %= SCREEN_HEIGHT;

    uint64_t mask = 1;
    mask <<= (SCREEN_WIDTH - 1 - col);

    bool toggled = screen[row] & mask;
    screen[row] ^= mask;
    return toggled;
}
