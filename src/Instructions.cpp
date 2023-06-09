#include "Chip8.h"

void Chip8::runInstruction() {
    switch ((opcode >> 12) & 0xF) {
        case 0x0:
            if (opcode == 0x00e0)
                std::invoke(&Chip8::op_00e0, this);
            else if (opcode == 0x00ee)
                std::invoke(&Chip8::op_00ee, this);
            else if (opcode == 0x0000)
                exit(0);
            break;
        case 0x1:
            std::invoke(&Chip8::op_1nnn, this);
            break;
        case 0x2:
            std::invoke(&Chip8::op_2nnn, this);
            break;
        case 0x3:
            std::invoke(&Chip8::op_3xkk, this);
            break;
        case 0x4:
            std::invoke(&Chip8::op_4xkk, this);
            break;
        case 0x5:
            if ((opcode & 0xF) == 0x0) std::invoke(&Chip8::op_5xy0, this);
            break;
        case 0x6:
            std::invoke(&Chip8::op_6xkk, this);
            break;
        case 0x7:
            std::invoke(&Chip8::op_7xkk, this);
            break;
        case 0x8:
            switch (opcode & 0xF) {
                case 0x0:
                    std::invoke(&Chip8::op_8xy0, this);
                    break;
                case 0x1:
                    std::invoke(&Chip8::op_8xy1, this);
                    break;
                case 0x2:
                    std::invoke(&Chip8::op_8xy2, this);
                    break;
                case 0x3:
                    std::invoke(&Chip8::op_8xy3, this);
                    break;
                case 0x4:
                    std::invoke(&Chip8::op_8xy4, this);
                    break;
                case 0x5:
                    std::invoke(&Chip8::op_8xy5, this);
                    break;
                case 0x6:
                    std::invoke(&Chip8::op_8xy6, this);
                    break;
                case 0x7:
                    std::invoke(&Chip8::op_8xy7, this);
                    break;
                case 0xE:
                    std::invoke(&Chip8::op_8xyE, this);
                    break;
            }
            break;
        case 0x9:
            std::invoke(&Chip8::op_9xy0, this);
            break;
        case 0xA:
            std::invoke(&Chip8::op_Annn, this);
            break;
        case 0xB:
            std::invoke(&Chip8::op_Bnnn, this);
            break;
        case 0xC:
            std::invoke(&Chip8::op_Cxkk, this);
            break;
        case 0xD:
            std::invoke(&Chip8::op_Dxyn, this);
            break;
        case 0xE:
            if ((opcode & 0xFF) == 0x9E)
                std::invoke(&Chip8::op_Ex9E, this);
            else if ((opcode & 0xFF) == 0xA1)
                std::invoke(&Chip8::op_ExA1, this);
            break;
        case 0xF:
            switch (opcode & 0xFF) {
                case 0x07:
                    std::invoke(&Chip8::op_Fx07, this);
                    break;
                case 0x0A:
                    std::invoke(&Chip8::op_Fx0A, this);
                    break;
                case 0x15:
                    std::invoke(&Chip8::op_Fx15, this);
                    break;
                case 0x18:
                    std::invoke(&Chip8::op_Fx18, this);
                    break;
                case 0x1E:
                    std::invoke(&Chip8::op_Fx1E, this);
                    break;
                case 0x29:
                    std::invoke(&Chip8::op_Fx29, this);
                    break;
                case 0x33:
                    std::invoke(&Chip8::op_Fx33, this);
                    break;
                case 0x55:
                    std::invoke(&Chip8::op_Fx55, this);
                    break;
                case 0x65:
                    std::invoke(&Chip8::op_Fx65, this);
                    break;
            }
            break;
    }
}

// clear display
void Chip8::op_00e0() { clear(); }

// return
void Chip8::op_00ee() {
    if (sp == 0) exit(0);
    sp--;
    pc = stack[sp];
}

// jump to nnn
void Chip8::op_1nnn() { pc = addr; }

// call subroutine at nnn
void Chip8::op_2nnn() {
    stack[sp] = pc;
    sp++;
    pc = addr;
}

// skip if Vx = kk
void Chip8::op_3xkk() {
    if (reg[x] == imm) pc += 2;
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

    for (int i = 0; i < (opcode & 0xF); i++) {  // scan through y coordinate
        u_int8_t line = ram[index + i];
        for (int j = 7; j >= 0; j--) {  // scan through x coordinate
            if (line & 1) reg[0xF] |= toggle(reg[y] + i, reg[x] + j);
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
