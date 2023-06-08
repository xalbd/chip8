# CHIP-8 Emulator

Chip-8 is a very small interpreted programming language developed in the 70s. I'm writing this emulator as an exercise to further understand CPUs and improve my C++.

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

## References

- http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
- https://github.com/mattmikolay/chip-8/wiki/Mastering-CHIP-8
