#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "memoryCommand.h"
#include "symbol.h"
#include "keyword.h"
#include "line.h"
#include "commandLine.h"

commandTable commands[] = {	{ "mov", 0, 0},
				{ "cmp", 2, 10	},
				{ "add",  2, 10 },
				{ "sub",  2, 11 },
				{ "lea", 4, 0	},
				{ "clr", 5, 10	},
				{ "not", 5, 11	},
				{ "inc", 5, 12	},
				{ "dec", 5, 13	},
				{ "jmp", 9, 10	},
				{ "bne", 9, 11	},
				{ "jsr", 9, 12	},
				{ "red", 12, 0	},
				{ "prn", 13, 0	},
				{ "rst", 14, 0	},
				{ "stop", 15, 0	} };

int opcodeCommand(char* command){
	int i;
	
	for(i = 0; i < NUM_COMMAND; i++) /*search in the command-table*/
		if(strcmp(commands[i].name, command) == 0) /*found the command*/
			return commands[i].opcode; /*command's opcode*/
	
	return 0; /*not found*/
}

int functCommand(char* command){
	int i;
	
	for(i = 0; i < NUM_COMMAND; i++) /*search in the command-table*/
		if(strcmp(commands[i].name, command) == 0) /*found the command*/
			return commands[i].funct; /*command's funct*/
	
	return 0; /*not found*/
}

int modeAddress(char* operand, char* command){
	int i;
	
	if(operand[0] == '#'){ /*immediate addressing*/
		if(strlen(operand) == 1) /*no number*/
			return 0;
		
		/*the operand must be an integer: */
		for(i = 1; operand[i] != '\0'; i++){
			if(i == 1){
				if(operand[i] != '-' && operand[i] != '+' && (operand[i] < '0' || operand[i] > '9')) /*not an integer*/
					return 0;
			}
			
			else if(operand[i] < '0' || operand[i] > '9') /*not an integer*/
				return 0;
		}
		return 1; /*integer*/
	}

	else if(operand[0] == '%'){ /*relative addressing*/
		if(strcmp(command, "jmp") != 0 && strcmp(command, "bne") != 0 && strcmp(command, "jsr") != 0) /*wrong addressing mode*/
			return 0;
		if(search(&(operand[1])) != EOF) /*the symbol in the symbol-table*/
			return ifExtern(&(operand[1])) ? 0 : 1; /*if it external symbol*/
		return EOF; /*the symbol not in the symbol-table*/
	}
	
	else if(reg(operand)) /*register direct addressing*/
		return 1;
	
	else /*direct addressing*/
		return search(operand) != EOF ? 1: EOF; /*if the symbol in the symbol-table*/
}

int modeToInt(char* operand){
	if(operand[0] == '#') /*immediate addressing*/
		return IMMEDIATE;
	
	else if(operand[0] == '%') /*relative addressing*/
		return RELATIVE;
	
	else if(reg(operand)) /*register direct addressing*/
		return REG_DIRECT;
	
	else /*direct addressing*/
		return DIRECT;
}

int printImgCode(FILE* ob, FILE* ext, char* command, char* list, int address){
	int source = 0, destination = 0, lenOprnd, num_oprnd = NUM_OPRND_THIRD; /*the number of operands*/
	char *operand;
	
	list = commaToSpace(list);
	lenOprnd = frsWordLen(list);
	
	operand = (char*)malloc(sizeof(char)*lenOprnd);
	sscanf(list, "%s", operand); /*get operand*/
	
	if(firstCommand(command)){ /*there are source and destination addresses*/
		num_oprnd = NUM_OPRND_FIRST;
		source = modeToInt(operand); /*source addressing*/
		
		/*go to the next operand: */
		free(operand);
		operand = NULL;
		
		list += lenOprnd;
		list = skipWhitespaces(list);/*go to the next operand*/
		
		lenOprnd = frsWordLen(list);
		operand = (char*)malloc(sizeof(char)*lenOprnd);
		sscanf(list, "%s", operand); /*get operand*/ /*get the next operand*/
		
		destination = modeToInt(operand); /*destination addressing*/
	}
	
	else if(secondCommand(command)){ /*there is destination addresses*/
		num_oprnd = NUM_OPRND_SEC;
		destination = modeToInt(operand); /*destination addressing*/
	}
	
	fprintf(ob, "%04d %X%X%X A\n", address, opcodeCommand(command), functCommand(command), source << DEST_BITS | destination);
	
	address++; /*one nore word (command)*/
	
	address = printImgList(ob, ext, list, num_oprnd, address);
	
	if(operand != NULL && strcmp(operand, "")){/*there is the operand*/
		free(operand);
		operand = NULL;
	}
	
	return address;
}

int printImgList(FILE* ob, FILE* ext, char* list, int num_oprnd, int address){
	char *operand;
	int lenOprnd;
	
	while(num_oprnd > 0){ /*there is more operand*/
		lenOprnd = frsWordLen(list);
		operand = (char*)malloc(sizeof(char)*lenOprnd);
		sscanf(list, "%s", operand); /*get operand*//*get operand*/
		
		list += strlen(operand); 
		list = skipWhitespaces(list);/*go to the next operand*/
		
		if(modeToInt(operand) == IMMEDIATE)/*immediate addressing*/
			fprintf(ob, "%04d %03X A\n", address, atoi( &(operand[1])) );
		
		else if(modeToInt(operand) == DIRECT){/*direct addressing*/
			if(ifExtern(operand)){/*external symbol*/
				fprintf(ob, "%04d %03X E\n", address, EXTERN_VAL);
				fprintf(ext, "%s %04d\n", operand, address);
			}
			else /*not external symbol*/
				fprintf(ob, "%04d %03X R\n", address, getVal(operand));
		}
		
		else if(modeToInt(operand) == RELATIVE)/*relative addressing*/
			fprintf(ob, "%04d %03X A\n", address, address - getVal( &(operand[1])) );
		
		else /*register direct addressing*/
			fprintf(ob, "%04d %03X A\n", address, 1 << atoi( &(operand[1])) );
		
		address++; /*one more word (operand)*/
		free(operand);
		operand = NULL;
		num_oprnd--;/*finish print for one operand*/
	}
	
	return address;
}
