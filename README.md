# Assembler Project - Final Project
This project is an Assembler written in the C programming language.
The assembler supports 16 different commands and different types of data (e.g. strings). 
The assembler is program that get names of files which written in assembly (specifically created for this project), for each file the assembler looks for errors, if there are errors, it print them, and if not it creates a file of machine code.

The commands it supports are as following: mov, cmp, add, sub, lea, clr, not, inc, dec, jmp, bne, jsr, red, prn, rts, stop

## The Computer
The computer in this project consists of a CPU, registers, and RAM. Part of the memory is used as a stack. The computer only works with integers, both positive and negative. There is no support for real numbers. Arithmetically, it works using the 2's completement method, and it supports characters that are represented in ascii code.

### The CPU (and registers)
The CPU has 8 general registers, all labled r + their index number (e.g. r0, r1.. r7), one status register- PSW (program status word), and program counter (PC). Each of these registers can contain 12 bits. The bits in each of those are labeled in the same way, the bit in the 0 index is the LSB (Least Significant Bit) while the bit in the 11th index is the MSB (Most Significant Bit).

### The Memory
The memory has 4096 word, all labled with a number from 0 to 4095. Each word has 12 bits. The bits are labeled in the same way as they are in the registers.

## running
The given assembly source files, must be in the same folder as the program's source files.
At "examples" folder, there are 3 examples for assembly valid files all labled with good + number + .as (e.g. good1.as, good2.as, good3.as), one assembly source file with errors, which named: wrong.as, and the files that the assembler created for the source files without errors.
When start running of program in the command line, need to write the names of assembly files withot the ending (.as).

Examples of program running, in a different situations:
![image](https://github.com/mich153/Assembler/assets/148886575/0872703f-7f48-4bd0-abb2-3e4ece0a39c4)

