#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "outPut.h"
#include "assembler.h"
#include "guidanceLine.h"
#include "keyword.h"
#include "line.h"
#include "memoryCommand.h"
#include "symbol.h"
#include "commandLine.h"

void makeOutput(FILE* file, char* name, int numLine){
	FILE *object = openFiles(name, ".ob"); /*make object file*/
	FILE *entries = openFiles(name, ".ent"); /*make entries file*/
	FILE *externals = openFiles(name, ".ext"); /*make externals file*/
	extern int ICF, DCF;
	int address = MIN_IC;
	char line[MAX_LINE_LEN] = "", *word = NULL, *temp;
	
	fprintf(object, "\t%d %d\n", ICF - MIN_IC, DCF);
	
	while(numLine > 0){ /*not end of file*/
		fgets(line, MAX_LINE_LEN, file);/*get line from the file*/
		temp = line;
		temp = skipWhitespaces(temp); /*go to word*/
		
		word = (char*)malloc(sizeof(char)*frsWordLen(temp));
		if(word == NULL){
			printf("Memory allocation problem, ending program.\n");
			exit(1);
		}
		sscanf(temp, "%s", word); /*get word*/
		
		/*go to the next word: */
		temp += frsWordLen(temp); 
		temp = skipWhitespaces(temp);
		
		if(word[strlen(word) - 1] == ':'){ /*it's symbol*/
			free(word); /*ignore symbols*/
			word = NULL;
			
			word = (char*)malloc(sizeof(char)*frsWordLen(temp));
			if(word == NULL){
				printf("Memory allocation problem, ending program.\n");
				exit(1);
			}
			sscanf(temp, "%s", word); /*get the next word*/
			
			/*go forward in the line: */
			temp += frsWordLen(temp); 
			temp = skipWhitespaces(temp);
		}
		
		if(firstCommand(word) || secondCommand(word) || thirdCommand(word)) /*command line*/
			address = printImgCode(object, externals, word, temp, address);
		
		else if(guidance(word)) /*guidance line*/
			address = printImgData(object, word, temp, address);
		
		free(word);
		word = NULL;
		numLine--; /*one line less to read*/
	}
	
	printEntries(entries); /*write in entries file*/
	
	fclose(object);
	fclose(entries);
	fclose(externals);
}

FILE* openFiles(char* name, char* ending){
	char *f_name = fullName(name, ending); /*the full name*/
	FILE *file = fopen(f_name, "w"); /*open new file*/
	
	if(f_name != NULL){ /*there is full name*/
		free(f_name);
		f_name = NULL;
	}
	
	return file;
}

char* fullName(char* name, char* ending){
	char *temp;
	int i;
	
	if(ending == NULL || name == NULL) /*no file's ending or name*/
		return NULL;
	
	else if(strcmp(ending, ".as") && strcmp(ending, ".ob") && strcmp(ending, ".ent") && strcmp(ending, ".ext")) /*wrong ending*/
		return NULL;
	
	else{
		temp = (char*)malloc(sizeof(char) * (strlen(name) + strlen(ending) + 1));
		if(temp == NULL){
			printf("Memory allocation problem, ending program.\n");
			exit(1);
		}
		
		for(i = 0; i < strlen(name); i++) /*copy the word*/
			temp[i] = name[i]; /*copy a charecter*/
		temp[strlen(name)] = '\0'; /*end of name*/
		
		strcat(temp, ending); /*add the ending*/
		
		return temp;
	}
}
