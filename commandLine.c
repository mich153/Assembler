#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "commandLine.h"
#include "line.h"
#include "symbol.h"
#include "keyword.h"
#include "memoryCommand.h"

int IC; /*instruction-counter*/

void startCommand(){
	IC = MIN_IC;
}

int doCommandLine(char* line, int numLine){
	char *command = (char*)malloc(sizeof(char)*frsWordLen(line));
	if(command == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	
	IC++; /*there is one more word (command)*/
	sscanf(line, "%s", command); /*get the command*/
	
	line += strlen(command); /*go to operand*/
	oprndList(line, command, numLine);/*check all of the operands*/
	
	free(command);
	command = NULL;
	
	return 1;
}

int numOperands(char* command){
	/*compare the amout of operand to the amount that need to be: */
	if(firstCommand(command))
		return NUM_OPRND_FIRST;
	
	else if(secondCommand(command))
		return NUM_OPRND_SEC;
	
	else if(thirdCommand(command))
		return NUM_OPRND_THIRD;
	
	return EOF;
}

int oprndList(char* list, char* command, int numLine){
	int num_oprnd = numOperands(command); /*the number of operand*/
	int i;
	char* oprnd; /*the operand*/
	list = commaToSpace(list);
	
	for(i = 0; i < num_oprnd; i++){ /*chack all af the operands*/
		list = skipWhitespaces(list); /*go to operand*/
		
		if(strcmp(list, "") == 0 || strcmp(list, "\n") == 0){ /*end of line*/
			printf("In line: %d, Too few operands to command '%s'.\n", numLine, command);
			return 0;
		}
		
		oprnd = (char*)malloc(sizeof(char)*frsWordLen(list));
		if(oprnd == NULL){
			printf("Memory allocation problem, ending program.\n");
			exit(1);
		}
		sscanf(list, "%s", oprnd); /*get the next operand*/
		
		if(modeAddress(oprnd, command) == 0){
			printf("In line: %d, wrong operand or mode addressing in the word '%s'.\n", numLine, oprnd);
			return 0;
		}
		
		IC++; /*there is one more word (operand)*/
		list += strlen(oprnd); /*go to the next operand*/
		free(oprnd);
		oprnd = NULL;
	}
	
	list = skipWhitespaces(list);
	if(strcmp(list, "\n") && strcmp(list, "")){/*more words left*/
		printf("In line: %d, Too many operands to command '%s'.\n", numLine, command);
		return 0;
	}
	
	return 1; /*no errors*/
}

int symbolOperand(char* command, char* line, int numLine){
	int existent = 1;/*if the symbol existent*/
	char *operand = NULL;
	int lenOprnd;
	line = commaToSpace(line);
	
	while(line != NULL && strcmp(line, "") && strcmp(line, "\n")){
		lenOprnd = frsWordLen(line);
		operand = (char*)malloc(sizeof(char)*lenOprnd);
		if(operand == NULL){
			printf("Memory allocation problem, ending program.\n");
			exit(1);
		}
		sscanf(line, "%s", operand);  /*get operand*/
		
		/*go to the next operand: */
		line += strlen(operand); 
		line = skipWhitespaces(line);
		
		if(modeAddress(operand, command) == EOF){ /*the operand is symbol that not defined*/
			printf("In line: %d, in the word: '%s', the symbol isn't defined in the file.\n", numLine, operand);
			existent = 0;
		}
		
		free(operand);
		operand = NULL;
	}
	
	return existent;
}
