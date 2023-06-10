#ifndef CHIP8_H_
#define CHIP8_H_

#include <Constants.h>

#include <cstdint>
#include <string>

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
    bool keys[16] = {};

    uint8_t delayTimer = 0;
    uint8_t soundTimer = 0;

    uint16_t opcode;
    uint8_t x, y;
    uint16_t addr, imm;
    void parseInstruction();

    uint32_t screen[SCREEN_HEIGHT * SCREEN_WIDTH] = {};
    void printStd();
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