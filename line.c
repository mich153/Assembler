#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "line.h"
#include "keyword.h"
#include "symbol.h"
#include "commandLine.h"
#include "guidanceLine.h"

int lineAnalys(char* line, int lineNum){
	int length = frsWordLen(line), legal = 1;
	char *word = (char*)malloc(sizeof(char)*length);
	if(word == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	sscanf(line, "%s", word); /*get the next word*/
	line = skipWhitespaces(line); /*go to the next word*/
	
	if(strcmp(line, "") == 0 || strcmp(line, "\n") == 0) /*empty line*/
		return 1;
	
	else if(word[length - 2] == ':' && word[0] != ':'){ /*symbol definition*/
		if(doSymbolDef(line, lineNum) == NULL) /*wrong definition*/
			legal = 0;
		if(lineAnalys(line + length, lineNum) == 0) /*error in the rest of the line*/
			legal = 0;
	}
	
	else if(firstCommand(word) || secondCommand(word) || thirdCommand(word)){ /*command line*/
		if(doCommandLine(line, lineNum) == 0)/*error in the command line*/
			legal = 0;
	}
	
	else if(word[0] == '.' && guidance( & (word[1]) )){ /*guidance line*/
		if(doGuidanceLine(line, lineNum) == 0)/*error in the guidance line*/
			legal = 0;
	}
	
	else if(word[0] != ':'){ /*wrong word*/
		printf("In line: %d, can't find the meaning of the word '%s'.\n", lineNum, word);
		lineAnalys(line + length, lineNum); /*look for errors later in the line*/
		legal = 0;
	}
	
	free(word);
	word = NULL;
	return legal;
}

char* skipWhitespaces(char* str){
	char letter;
	int max = strlen(str), i = 0;
	
	do{
		sscanf(str, "%c", &letter); /*the next charecter*/
		i++;
		
		if((letter == ' ' || letter == '\t') && i < max)
			str++; /*go forward in the string*/
		
	}while((letter == ' ' || letter == '\t') && i < max); /*there is whitespaces and the string isn't end*/
	
	return str;
}

int frsWordLen(char* str){
	int length = 0;
	char letter = 0;
	int max = strlen(str), i;
	
	str = skipWhitespaces(str);
	
	if(str == NULL) /*no words in the line*/
		return 0;
	
	for(i = 0; inWord(letter) && i < max; i++){ /*go forward in the word*/
		sscanf(str, "%c", &letter);
		length++; 
		str++;
	}
	
	return length;
}

int inWord(char letter){
	return !(letter == ' ' || letter == '\t' || letter =='\n'  || letter == EOF); /*the word and the line is not end*/
}

char* commaToSpace(char* line){
	int i;
	
	for(i = 0; line[i] != '\0'; i++){ /*read the line*/
		if(line[i] == ',') /*comma*/
			line[i] = ' '; /*change comma to space*/
	}
	
	return line;
}

int errorList(char* list, int numLine){
	int comma = 0, space = 0, i, legal = 1;
	int length = strlen(list);
	
	list = skipWhitespaces(list);
	
	for(i = 0; i < length; i++){ /*go forward in the list*/
		if(list[i] == ','){ /*comma*/
			if(comma == 1){ /*two commas consecutively*/
				printf("In line: %d, missing argument between two comas\n", numLine);
				legal = 0;
			}
			comma = 1;
			space = 0;
		}

		else if(list[i] == ' ' || list[i] == '\t')
			space = 1;

		else{
			if(space == 1 && comma == 0){
				printf("In line: %d, missing comma between two argumants\n", numLine);
				legal = 0;
			}
			comma = 0;
			space = 0;
		}
	}
	
	return legal;
}

int entAndExt(char* line, int numLine){
	int ret_val = 1;
	char *word = (char*)malloc(sizeof(char)*frsWordLen(line));
	line = skipWhitespaces(line); /*go to the word*/
	if(word == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	sscanf(line, "%s", word); /*get the word*/
	
	/*go to the next word: */
	line += frsWordLen(line); 
	line = skipWhitespaces(line);
	
	if(word[strlen(word) - 1] == ':'){ /*it's symbol*/
		free(word); /*ignore symbols*/
		word = NULL;
		
		word = (char*)malloc(sizeof(char)*frsWordLen(line));
		if(word == NULL){
			printf("Memory allocation problem, ending program.\n");
			exit(1);
		}
		sscanf(line, "%s", word); /*get the word*/
		
		/*go to the next word: */
		line += frsWordLen(line);
		line = skipWhitespaces(line);
	}
		
	if(strcmp(word, ".entry") == 0){/*it's entry guidance*/
		if(entrySymbol(line, numLine) == ERROR)/*there is error with the symbol*/
			ret_val = 0;
	}
	
	else if(firstCommand(word) || secondCommand(word) || thirdCommand(word)){/*it's command*/
		if(symbolOperand(word, line, numLine) == ERROR)/*there is wrong operand*/
			ret_val = 0;
	}
	
	else
		ret_val = EOF;
	
	free(word);
	word = NULL;
	
	return ret_val;
}
