#include <random>

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
void Chip8::op_00e0() { memset(screen, 0, sizeof(screen)); }

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
    bool carry = 255 < reg[x] + reg[y];
    reg[x] += reg[y];
    reg[0xF] = carry;
}

// Vx -= Vy, VF = not borrow
void Chip8::op_8xy5() {
    bool notborrow = reg[x] > reg[y];
    reg[x] -= reg[y];
    reg[0xF] = notborrow;
}

// Vx = Vy >> 1, VF = original LSB
void Chip8::op_8xy6() {
    bool lsb = reg[y] & 1;
    reg[x] = reg[y] >> 1;
    reg[0xF] = lsb;
}

// Vx = Vy - Vx, VF = not borrow
void Chip8::op_8xy7() {
    bool notborrow = reg[y] > reg[x];
    reg[x] = reg[y] - reg[x];
    reg[0xF] = notborrow;
}

// Vx = Vy << 1, VF = original MSB
void Chip8::op_8xyE() {
    bool msb = reg[y] >> 7;
    reg[x] = reg[y] << 1;
    reg[0xF] = msb;
}

// skip if Vx != Vy
void Chip8::op_9xy0() {
    if (reg[x] != reg[y]) pc += 2;
}

// index = nnn
void Chip8::op_Annn() { index = addr; }

// jump to nnn + V0
void Chip8::op_Bnnn() { pc = addr + reg[0x0]; }

// Vx = random byte & kk
void Chip8::op_Cxkk() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 0xFF);
    reg[x] = distr(gen);
}

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
void Chip8::op_Ex9E() {
    if (keys[reg[x]]) pc += 2;
}

// skip if key Vx is not pressed
void Chip8::op_ExA1() {
    if (!keys[reg[x]]) pc += 2;
}

// Vx = delayTimer
void Chip8::op_Fx07() { reg[x] = delayTimer; }

// wait for key, Vx = key
void Chip8::op_Fx0A() {
    for (int i = 0; i < 16; i++) {
        if (keys[i]) {
            reg[x] = i;
            return;
        }
    }

    pc -= 2;
}

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
    for (int i = 0; i <= x; i++) {
        ram[index + i] = reg[i];
    }
}

// V0 ... Vx = ram[index ... index + x]
void Chip8::op_Fx65() {
    for (int i = 0; i <= x; i++) {
        reg[i] = ram[index + i];
    }
}
