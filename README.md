# CHIP-8 Emulator

Chip-8 is a very small interpreted programming language developed in the 70s. It is a simple language to emulate and is a good example of how a CPU works at a lower level.

## Chip-8 Information

Chip-8 has 16 16-bit general registers, 4kb of memory, interfaces through the user by placing sprites on a 64x32 monochrome screen and queries for input on a 16-key keypad.

Every instruction in Chip-8 is two bytes long. Because Chip-8 is an interpreted language and not machine code, it is near-impossible to create a cycle-accurate emulation. Typically, each opcode is simply executed after a small delay in order to create roughly acccurate timings (as does this emulator).

## Implementation Notes

More modern versions of Chip-8 like SChip and Chip-XO add extra instructions or modify the behavior of existing ones. This interpreter is based off of the implementation and quirks of the original Chip-8 interpreter, and as such, many modern programs will not run correctly.

## To-do List

- [x] Implement opcode parser
- [x] Console-based display (ASCII) + basic debugging data
- [x] Implement SDL for display
- [x] Implement input
- [x] Test all opcodes thoroughly
- [ ] Fix base Chip-8 implementation quirks
- [ ] Command line arguments for refresh rate, ROM selection
- [x] Implement accurate-ish 60Hz timer

## Compiling and Running

Requires C++17, cmake, and SDL2. Run these commands from the source directory.

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./chip8
```

The keys of the Chip-8 are mapped to 1-4, Q-R, A-F, and Z-V for user interaction.

## References

- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP-8
- https://github.com/Timendus/chip8-test-suite
- https://chip8.gulrak.net/
