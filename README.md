# CHIP-8 Emulator

Chip-8 is a very small interpreted programming language developed in the 70s. It is a simple language to emulate and is a good example of how a CPU works at a lower level.

## Chip-8 Information

Chip-8 has 16 16-bit general registers, 4kb of memory, interfaces through the user by placing sprites on a 64x32 monochrome screen and queries for input on a 16-key keypad.

Every instruction in Chip-8 is two bytes long. Because Chip-8 is an interpreted language and not machine code, it is near-impossible to create a cycle-accurate emulation. Typically, each opcode is simply executed after a small delay in order to create roughly acccurate timings (as does this emulator).

## Pong

Note that the flickering/wraparound behavior is from the ROM used here, not from the implementation.

https://github.com/xalbd/chip8/assets/119540449/e1e9c730-0ca3-4008-a367-0c59221e80d3

## Implementation Notes

More modern versions of Chip-8 like SChip and Chip-XO add extra instructions or modify the behavior of existing ones. This interpreter is based off of the implementation and quirks of the original Chip-8 interpreter, and as such, many modern programs will not run correctly.

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
