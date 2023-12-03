# Assembler Project - Final Project
This project is an Assembler written in the C programming language.
The assembler supports 16 different commands and different types of data (e.g. strings). 
The assembler is program that get names of files which written in Assembly (specifically created for this project), for each file the assembler looks for errors, if there are errors, it print them, and if not it creates a file of machine code.

The commands it supports are as following: mov, cmp, add, sub, lea, clr, not, inc, dec, jmp, bne, jsr, red, prn, rts, stop

## The Computer
The computer in this project consists of a CPU, registers, and RAM. Part of the memory is used as a stack. The computer only works with integers, both positive and negative. There is no support for real numbers. Arithmetically, it works using the 2's completement method, and it supports characters that are represented in ascii code.

### The CPU (and registers)
The CPU has 8 general registers, all labled r + their index number (e.g. r0, r1.. r7), one status register- PSW (program status word), and program counter (PC). Each of these registers can contain 12 bits. The bits in each of those are labeled in the same way, the bit in the 0 index is the LSB (Least Significant Bit) while the bit in the 11th index is the MSB (Most Significant Bit).

### The Memory
The memory has 4096 word, all labled with a number from 0 to 4095. Each word has 12 bits. The bits are labeled in the same way as they are in the registers.
