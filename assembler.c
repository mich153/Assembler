#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembler.h"
#include "line.h"
#include "commandLine.h"
#include "guidanceLine.h"
#include "keyword.h"
#include "symbol.h"
#include "memoryCommand.h"
#include "outPut.h"

extern int IC, DC; /*instruction and data counters*/
int ICF, DCF; /*the final value of conters*/

int main(int argc, char* argv[]){
	int i;
	if(argc == 1){/*no files sent*/
		printf("No sent any files.\n");
		return 0;
	}
	for(i = 1; i < argc; i++)/*compile all of files*/
		start(argv[i]);
	
	return 0;
}

int start(char* file){
	FILE *pFile; /*pointer to file*/
	int numLine = 0; /*the number of lines*/
	
	/*copy file's name: */
	char *name = fullName(file, ".as");
	pFile = fopen(name, "r");
	
	if (pFile == NULL){/*there isn't file*/
		printf("There isn't source file with the name '%s'.\n", name);
		return 0;
	}
	
	printf("Compile the source file '%s'.\n", name);
	
	numLine = firstPass(pFile); /*pass on the file*/
	
	if(numLine != EOF){/*the first pass success*/
		fseek(pFile, 0L, SEEK_SET); /*start read from the beginning of the file*/
		
		if(secondPass(pFile)){ /*the second pass success*/
			fseek(pFile, 0L, SEEK_SET); /*start read from the beginning of the file*/
			printf("The compilation success, make output files.\n");
			makeOutput(pFile, file, numLine);/*do output files*/
		}
		
		else{ /*the second pass failed*/
			printf("The compilation failed.\n");
			return 0;
		}
	}
	
	else{ /*the first pass failed*/
		printf("The compilation failed.\n");
		return 0;
	}
	
	fclose(pFile); /*close the file*/
	endSymbol(); /*end work with symbols*/
	free(name);
	name = NULL;
	
	return 1; /*everything success*/
}

int firstPass(FILE* file){
	int error = 0; /*if there is error the file*/
	int numLine = 0; /*count the number of line*/
	char line[MAX_LINE_LEN] = "";
	char* temp;
	
	startSymbol();
	startCommand();
	startGuidance();
	
	do{
		temp = fgets(line, MAX_LINE_LEN, file);
		if(temp == NULL)/*end of file*/
			break;
		
		numLine++; /*one more line*/
		if(lineAnalys(line, numLine) == 0) /*there is error in the line*/
			error = 1;
		
	}while(temp != NULL); /*not end of file*/
	
	ICF = IC; /*save the final value*/
	DCF = DC; /*save the final value*/
	
	updateVal(ICF); /*update the data-symbol's value*/
	if(error == 1) /*illegal file*/
		return EOF;
	
	return numLine;
}

int secondPass(FILE* file){
	char line[MAX_LINE_LEN] = "", *temp;
	int numLine = 0, legal = 1;
	
	do{
		temp = fgets(line, MAX_LINE_LEN, file);/*get line from the file*/
		numLine++; /*one more line*/
		
		if(entAndExt(line, numLine) == 0) /*there is error*/
			legal = 0;
			
	}while(temp != NULL);
	
	return legal;
}
