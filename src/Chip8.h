#ifndef CHIP8_H_
#define CHIP8_H_

#include <cstdint>
#include <string>

const int CYCLE_LEN_MS = 1;
const u_int16_t START_ADDRESS = 0x200;
const u_int16_t FONT_START_ADDRESS = 0x50;
const int FONT_HEIGHT = 5;
const int FONT_MEMSIZE = FONT_HEIGHT * 16;
const u_int8_t FONT[FONT_MEMSIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
    0x20, 0x60, 0x20, 0x20, 0x70,  // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
    0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
    0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
    0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
    0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
    0xF0, 0x80, 0xF0, 0x80, 0x80   // F
};
const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;

class Display;

class Chip8 {
   public:
    Chip8(std::string romFile);
    ~Chip8();
    void run();

   private:
    void loadROM(std::string romFile);
    void cycle();
    void printStatus();

    uint8_t ram[4096] = {};
    uint8_t reg[16] = {};
    uint16_t stack[16] = {};
    uint16_t index = 0;
    uint16_t pc = 0;
    uint8_t sp = 0;

    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

    uint16_t opcode;
    uint8_t x, y;
    uint16_t addr, imm;
    void parseInstruction();

    uint64_t screen[SCREEN_HEIGHT] = {};
    void printStd();
    void clear();
    bool toggle(u_int8_t row, u_int8_t col);

    Display* display;

    void runInstruction();
    void op_00e0();
    void op_00ee();
    void op_1nnn();
    void op_2nnn();
    void op_3xkk();
    void op_4xkk();
    void op_5xy0();
    void op_6xkk();
    void op_7xkk();
    void op_8xy0();
    void op_8xy1();
    void op_8xy2();
    void op_8xy3();
    void op_8xy4();
    void op_8xy5();
    void op_8xy6();
    void op_8xy7();
    void op_8xyE();
    void op_9xy0();
    void op_Annn();
    void op_Bnnn();
    void op_Cxkk();
    void op_Dxyn();
    void op_Ex9E();
    void op_ExA1();
    void op_Fx07();
    void op_Fx0A();
    void op_Fx15();
    void op_Fx18();
    void op_Fx1E();
    void op_Fx29();
    void op_Fx33();
    void op_Fx55();
    void op_Fx65();
};

#endif  // CHIP8_H_