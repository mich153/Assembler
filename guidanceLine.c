#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "guidanceLine.h"
#include "keyword.h"
#include "line.h"
#include "symbol.h"

int DC; /*data-counter*/

void startGuidance(){
	DC = MIN_DC;
}

int doGuidanceLine(char* line, int numLine){
	int legal = 1; /*if it's legal list*/
	int lenGuid = frsWordLen(line);
	char *guid = (char*)malloc(sizeof(char)*lenGuid);
	sscanf(line, "%s", guid);
	
	line += strlen(guid);
	
	if(strcmp(guid, ".data") == 0){ /*data guidance*/
		if(data(line, numLine) == 0) /*error in data line*/
			legal = 0;
	}
	
	else if(strcmp(guid, ".string") == 0){ /*string guidance*/
		if(string(line, numLine) == 0) /*error in string line*/
			legal = 0;
	}
	
	else if(strcmp(guid, ".entry") == 0){ /*entry guidance*/
		if(entry(line, numLine) == 0) /*error in entry line*/
			legal = 0;
	}
	
	else if(strcmp(guid, ".extern") == 0){ /*external guidance*/
		if(external(line, numLine) == 0) /*error in external line*/
			legal = 0;
	}
	
	free(guid);
	guid = NULL;
	
	return legal;
}

int data(char* list, int numLine){
	int num, temp, numOprnd = 0;
	int legal = 1; /*if it's legal list*/
	
	if(errorList(list, numLine) == 0) /*problem with syntactic structer of the list*/
		legal = 0;
	list = commaToSpace(list); /*change the commas to spaces*/
	
	do{
		temp = sscanf(list, "%d", &num); /*get number*/
		
		if(temp == 0){ /*wrong parameter*/
			printf("In line: %d, all of the parameters should be integers in '.date' guidance.\n", numLine);
			numOprnd++; /*one more operand*/
			legal = 0;
		}
		
		else if(temp == EOF){ /*end of list*/
			if(numOprnd == 0){ /*no parameters in the list*/
				printf("In line: %d, should be minimum one parameter in '.date' guidance.\n", numLine);
				legal = 0;
			}
		}
		
		else{ /*legal operand*/
			DC++; /*one more data*/
			numOprnd++; /*one more operand*/
		}
		
		/*go to the next operand: */
		list += frsWordLen(list);
		list = skipWhitespaces(list);
		
	}while(temp != EOF);/*not end of list*/
	
	return legal;
}

int string(char* line, int numLine){
	line = skipWhitespaces(line);
	
	if(line[0] != '"'){/*not string*/
		printf("In line: %d, should be string as parameter in '.string' guidance.\n",numLine);
		return 0;
	}
	
	line++;
	
	while(*line != '\0' && *line != '"'){/*not end of list or line*/
		line++;/*continue in the word*/
		DC++;
	}
	
	if(*line == '\0'){/*not string*/
		printf("In line: %d, should be string as parameter in '.string' guidance.\n",numLine);
		return 0;
	}
	
	else{
		line++; /*skip quotation marks*/
		/*check the line duration: */
		line = skipWhitespaces(line);
		if(strcmp(line, "") && strcmp(line, "\n")){/*there is more parameter*/
			printf("In line: %d, should be only one parameter in '.string' guidance.\n",numLine);
			return 0;
		}
	}
	
	return 1;
}

int entry(char* line, int numLine){
	int lenSym = frsWordLen(line), legal = 1;
	char *symbol = (char*)malloc(sizeof(char)*lenSym);
	if(symbol == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	line = skipWhitespaces(line);/*go to the symbol*/
	sscanf(line, "%s", symbol); /*get the symbol parameter*/
	
	if(strcmp(symbol, "") == 0 || strcmp(symbol, "\n") == 0){ /*there isn't symbol*/
		printf("In line: %d, should be only one parameter in '.entry' guidance.\n",numLine);
		return 0;
	}
	
	
	/*check if there are more parameters: */
	line += lenSym; 
	line = skipWhitespaces(line);/*go to the next word*/
		
	if(strcmp(line, "") && strcmp(line, "\n")){ /*there is more parameter*/
		printf("In line: %d, should be only one parameter in '.entry' guidance.\n",numLine);
		legal = 0;
	}
	
	free(symbol);
	symbol = NULL;
	
	return legal;
}

int external(char* line, int numLine){
	int legal = 1;
	int lenSym = frsWordLen(line);
	char *symbol = (char*)malloc(sizeof(char)*lenSym);
	
	if(symbol == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	sscanf(line, "%s", symbol);/*get the next word*/
	
	if(strcmp(symbol, "") == 0 || strcmp(symbol, "\n") == 0){ /*there isn't symbol*/
		printf("In line: %d, should be minimum one parameter in '.extern' guidance.\n",numLine);
		return 0;
	}
	
	else if(externSymbol(symbol, numLine) == 0) /*there is error*/
		legal = 0;
	
	/*check if there are more parameters: */
	line += lenSym; /*go to the next word*/
	line = skipWhitespaces(line);
	
	if(strcmp(line, "") && strcmp(line, "\n")){ /*there are more parameters*/
		printf("In line: %d, should be only one parameter in '.extern' guidance.\n",numLine);
		legal = 0;
	}
	
	free(symbol);
	symbol = NULL;
	
	return legal;
}

int printImgData(FILE* file, char* guidance, char* list, int address){
	list = commaToSpace(list); /*change the commas to spaces*/
	
	if(strcmp(guidance, ".data")) /*data guidance*/
		while(list != NULL && strcmp(list, "\n")){/*not end of list*/
			list = skipWhitespaces(list); /*go to number*/
			
			fprintf(file, "%04d %03X A\n", address, atoi(list));
			
			address++; /*one more word (number)*/
			list += frsWordLen(list);/*go to the next number*/
		}
	
	else if(strcmp(guidance, ".string")){ /*string guidance*/
		list = skipWhitespaces(list); /*go to number*/
		list++; /*ignore from " */
		
		while(*list != '"'){ /*not end of string*/
			fprintf(file, "%04d %03X A\n", address, *list);
			
			address++; /*one more word (charecter)*/
			list++;/*go to the next charecter*/
		}
		
		fprintf(file, "%04d %03X A\n", address, '\0'); /*end of string*/
	}
	
	return address;
}
