/*Express command word in the computer's memory (opcode + funct + mode addressing)*/

#define NUM_COMMAND 16
/*the number of commands*/

#define MAX_COM_LEN 5
/*the maximum length of command*/

#define IMMEDIATE 0
/*immediate addressing's values*/

#define DIRECT 1
/*direct addressing's value*/

#define RELATIVE 2
/*relative addressing's values*/

#define REG_DIRECT 3
/*register direct addressing's values*/

typedef struct commandTable{
	char name[MAX_COM_LEN];
	int opcode;
	int funct;
}commandTable;

int opcodeCommand(char*); /*get command's name and return its opcode, or 0 if it's not a command*/

int functCommand(char*); /*get command's name and return its funct, or 0 if it's not a command*/

int modeAddress(char*, char*); /*get operand (with its modes addressing) and the command, 
return 1 if the modes addressing is legal, 0 if not, or EOF if the operand is symbol that there isn't in the symbol-table yet*/

int modeToInt(char*); /*get operand with its modes addressing and return the addressing mode's value*/

int printImgCode(FILE*, FILE*, char*, char*, int);/*get pointer to object file, pointer to externals file, the command, the list of operands and the address of the memory,print to the object file the image machine code for all of the words from the command line in format to object file, 
if there is external symbol so print to externals file the symbol, return the new address*/

int printImgList(FILE*, FILE*, char*, int, int);/*get pointer to object file, pointer to externals file, list of operands, the number of operands and the address of the memory, print to object the file the image machine code for all of the words from the list in format to object file, 
if there is external symbol so print to externals file the symbol,return the new address*/
