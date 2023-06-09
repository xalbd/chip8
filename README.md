# CHIP-8 Emulator

Chip-8 is a very small interpreted programming language developed in the 70s. It is a simple language to emulate and is a good example of how a CPU works at a lower level.

## Chip-8 Information

Chip-8 has 16 16-bit general registers, 4kb of memory, interfaces through the user by placing sprites on a 64x32 monochrome screen and queries for input on a 16-key keypad.

Every instruction in Chip-8 is two bytes long. Because Chip-8 is an interpreted language and not machine code, it is near-impossible to create a cycle-accurate emulation. Typically, each opcode is simply executed after a small delay in order to create roughly acccurate timings (as does this emulator).

## To-do List

- [x] Implement opcode parser
- [x] Console-based display (ASCII) + basic debugging data
- [ ] Strengthen integer typing checks
- [ ] Implement SDL for display
- [ ] Implement input
- [ ] Test all opcodes thoroughly
- [ ] Add debugging mode (live dissasembly, registers, RAM)
- [ ] Implement sound (coupled to main loop timing)
- [ ] Slightly more accurate timings for opcodes
- [ ] Toggles for differences in Chip-8 specifications/implementations
- [ ] Illegal opcodes

## Compiling and Running

Requires C++17, cmake, and SDL2. Run these commands from the source directory.

```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
$ ./chip8
```

~~The keys of the Chip-8, 0-9 and A-F are mapped to \_\_ for user interaction.~~

~~Open-source ROMs are included in this repository. To run them, run \_\_.~~

## References

- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP-8
