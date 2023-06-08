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
    auto time = std::chrono::high_resolution_clock::now();
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        if (now - time > std::chrono::milliseconds(CYCLE_LEN_MS)) {
            time = now;
            cycle();  // delay
            display->printStd();
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
        char *rom = new char[rom_size];

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
}

void Chip8::parseInstruction() {
    x = opcode & (0xF << 8);
    y = opcode & (0xF << 4);
    imm = opcode & 0xFF;
    addr = opcode & 0xFFF;
}

void Chip8::runInstruction() { std::invoke(&Chip8::op_00e0, this); }

// clear display
void Chip8::op_00e0() { display->clear(); }

// return
void Chip8::op_00ee() {
    pc = stack[sp];
    sp--;
}

// jump to nnn
void Chip8::op_1nnn() { pc = addr; }

// call subroutine at nnn
void Chip8::op_2nnn() {
    sp++;
    stack[sp] = pc;
    pc = addr;
}

// skip if Vx != kk
void Chip8::op_4xkk() {
    if (reg[x] != imm) pc += 2;
}

// skip if Vx = Vy
void Chip8::op_5xy0() {
    if (reg[x] == reg[y]) pc += 2;
}

// Vx = kk
void Chip8::op_6xkk() { reg[x] = imm; }

// Vx += kk
void Chip8::op_7xkk() { reg[x] += imm; }

// Vx = Vy
void Chip8::op_8xy0() { reg[x] = reg[y]; }

// Vx |= Vy
void Chip8::op_8xy1() { reg[x] |= reg[y]; }

// Vx &= Vy
void Chip8::op_8xy2() { reg[x] &= reg[y]; }

// Vx ^= Vy
void Chip8::op_8xy3() { reg[x] ^= reg[y]; }

// Vx += Vy, VF = carry
void Chip8::op_8xy4() {
    int total = reg[x] + reg[y];
    reg[0xF] = total > 255;
    reg[x] += reg[y];
}

// Vx -= Vy, VF = not borrow
void Chip8::op_8xy5() {
    reg[0xF] = reg[x] > reg[y];
    reg[x] -= reg[y];
}

// Vx = Vy >> 1, VF = original LSB
void Chip8::op_8xy6() {
    reg[0xF] = reg[y] & 1;
    reg[x] = reg[y] >> 1;
}

// Vx = Vy - Vx, VF = not borrow
void Chip8::op_8xy7() {
    reg[0xF] = reg[y] > reg[x];
    reg[x] = reg[y] - reg[x];
}

// Vx = Vy << 1, VF = original MSB
void Chip8::op_8xyE() {
    reg[0xF] = reg[y] >> 0xF;
    reg[x] = reg[y] << 1;
}

// skip if Vx != Vy
void Chip8::op_9xy0() {
    if (reg[x] != reg[y]) pc += 2;
}

// index = nnn
void Chip8::op_Annn() { index = imm; }

// jump to nnn + V0
void Chip8::op_Bnnn() { pc = imm + reg[0x0]; }

// Vx = random byte & kk
void Chip8::op_Cxkk() { return; }

// display sprite @ location index at (Vx, Vy), set VF = collision
void Chip8::op_Dxyn() {
    reg[0xF] = 0;

    for (int i = 0; i < (opcode & 0xF); i++) {
        u_int8_t line = ram[index + i];
        for (int j = 7; j >= 0; j--) {
            if (line & 1) reg[0xF] |= display->toggle(reg[x] + i, reg[y] + j);
            line >>= 1;
        }
    }
}

// skip if key Vx is pressed
void Chip8::op_Ex9E() { return; }

// skip if key Vx is not pressed
void Chip8::op_ExA1() { return; }

// Vx = delayTimer
void Chip8::op_Fx07() { reg[x] = delayTimer; }

// wait for key, Vx = key
void Chip8::op_Fx0A() { return; }

// delayTimer = Vx
void Chip8::op_Fx15() { delayTimer = reg[x]; }

// soundTimer = Vx
void Chip8::op_Fx18() { soundTimer = reg[x]; }

// index += Vx
void Chip8::op_Fx1E() { index += reg[x]; }

// index = font sprite for digit Vx
void Chip8::op_Fx29() { index = FONT_START_ADDRESS + FONT_HEIGHT * reg[x]; }

// hundreds, tens, ones digit of decimal Vx placed into ram[index, index + 1, index + 2]
void Chip8::op_Fx33() {
    ram[index] = reg[x] / 100;
    ram[index + 1] = (reg[x] / 10) % 10;
    ram[index + 2] = reg[x] % 10;
}

// ram[index ... index + x] = V0 ... Vx
void Chip8::op_Fx55() {
    for (int i = 0; i < x; i++) {
        ram[index + i] = reg[i];
    }
}

// V0 ... Vx = ram[index ... index + x]
void Chip8::op_Fx65() {
    for (int i = 0; i < x; i++) {
        reg[i] = ram[index + i];
    }
}