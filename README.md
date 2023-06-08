# CHIP-8 Emulator

Chip-8 is a very small interpreted programming language developed in the 70s. It's a simple language to emulate and is a nice exercise to understand how basic low-level principles work before moving on to creating more complex emulators.

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

## Compiling and Running

Requires C++17, make, and ~~SDL2~~.

```
$ make
$ ./run
```

The keys of the Chip-8, 0-9 and A-F are mapped to \_\_ for user interaction.

## References

- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP-8
