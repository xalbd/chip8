# CHIP-8 Emulator

Chip-8 is a very small interpreted programming language developed in the 70s. I'm writing this emulator as an exercise to further understand CPUs and improve my C++.

## To-do List

- [ ] Implement opcode parser
- [ ] Strengthen integer typing checks (bitsets everywhere?)
- [ ] Implement SDL for display
- [ ] Add debugging mode (live dissasembly, registers, RAM)
- [ ] Implement input
- [ ] Test all opcodes
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
