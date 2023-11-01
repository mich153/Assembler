#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "line.h"
#include "keyword.h"
#include "commandLine.h"

symbolTable *head; /*pointer to the symbol-table*/

void startSymbol(){
	head = NULL;
}

char* doSymbolDef(char* line, int numLine){
	extern int IC, DC;
	char *name;
	char *next; 
	
	name = symbolName(line, numLine); /*the name of symbol*/
	
	if(name == NULL)
		return NULL;
	
	/*go to the next word: */
	line += strlen(name) + 1;
	line = skipWhitespaces(line); 
	
	next = (char*)calloc(frsWordLen(line), sizeof(char));
	if(next == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	
	line = skipWhitespaces(line);
	sscanf(line, "%s", next); /*get the next word*/
	
	if(firstCommand(next) || secondCommand(next) || thirdCommand(next)) /*symbol in command line*/
		addSymbol(name, IC, "code"); /*add to the symbol-table*/
	
	else if(next[0] == '.' && guidance(&(next[1])) && strcmp(next, ".entry") && strcmp(next, ".extern"))
		/*symbol in guidance line (ignore from the symbol in entry or extern guidance line)*/
		addSymbol(name, DC, "data"); /*add to the symbol-table*/
	
	else if(strcmp(next, ".entry") && strcmp(next, ".extern")){ 
		/*no command and no guidance in the line (ignore from the symbol in entry or extern guidance line)*/
		printf("In line: %d, the next word '%s' is not a command or guidance.\n", numLine, next);
		free(name);
		name = NULL;
		return NULL;
	}
	
	return name;
}

char* symbolName(char* line, int lineNum){
	char *def, *next, *return_val = NULL;
	int lenDef, lenNext;
	
	lenDef = frsWordLen(line);
	def = (char*)malloc(sizeof(char)*(lenDef + 1));
	if(def == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	sscanf(line, "%s", def); /*the definition word*/
	
	line += lenDef; /*go to the next word*/
	line = skipWhitespaces(line);
	
	lenNext = frsWordLen(line);
	next = (char*)malloc(sizeof(char)*lenNext);
	if(next == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	sscanf(line, "%s", next); /*the next word*/
	
	if(def[strlen(def) - 1] == ':') /*it is definition of symbol*/
		def[strlen(def) - 1] = '\0';
	
	if(search(def) != EOF && strcmp(next, ".entry") != 0 && strcmp(next, ".extern") != 0)
		/*the symbol definded before*/
		printf("In line: %d, the symbol '%s' is already defined.\n", lineNum, def);
	
	else if(legalName(def) == 0)/*the symbol's name is illegal*/
		printf("In line: %d, illegal symbol name: '%s'.\n", lineNum, def);
	
	else /*no problems*/
		return_val = def;
	
	free(next);
	next = NULL;
	
	return return_val;
}

void addSymbol(char* name, int val, char* att){
	symbolTable* temp = head;
	
	if(head == NULL){ /*no list*/
		head = (symbolTable*)malloc(sizeof(symbolTable)); /*create new list*/
		initSymbol(head, name, val, att); /*initiallize the new list*/
		head->next = NULL;
		return;
	}
	
	while(temp->next != NULL) /*go to the end of list*/
		temp = temp->next;
	
	temp->next = (symbolTable*)malloc(sizeof(symbolTable)); /*create new symbol*/
	initSymbol(temp->next, name, val, att); /*initiallize the new symbol*/
	temp->next->next = NULL;
	return;
}

void initSymbol(symbolTable* symbol, char* name, int val, char* att){
	int i;
	
	/*copy the name: */
	symbol->name = (char*)malloc(sizeof(name) * (strlen(name) + 1));
	for(i = 0; i < strlen(name); i++)
		symbol->name[i] = name[i]; /*copy a charecter*/
	symbol->name[strlen(name)] = '\0'; /*end of name*/
	
	symbol->value = val; /*set value*/
	symbol->isExtern = 0; /*no information about this yet*/
	symbol->isEntry = 0; /*no information about this yet*/
	
	if(att != NULL && strcmp(att, "data") == 0) /*data attributes*/
		symbol->isData = 1;
	
	else if(att != NULL && strcmp(att, "code") == 0) /*code attributes*/
		symbol->isCode = 1;
	
	else if(att != NULL && strcmp(att, "extern") == 0) /*code attributes*/
		symbol->isExtern = 1;
}

int search(char* name){
	int pos = 1; /*the position*/
	symbolTable *temp = head;
	
	if (head == NULL) /*there isn't any symbol*/
		return EOF;
	
	while(temp != NULL){ /*the symbol-table not end*/
		if(strcmp(temp->name, name) == 0) /*the same name*/
			return pos; /*the symbol is found*/
		
		temp = temp->next;/*go forward in the symbol-table*/
		pos++;
	}
	
	return EOF;
}

int legalName(char* name){
	int length = strlen(name);
	int i;
	
	if(strcmp(name, "") == 0) /*no definition*/
		return -1;
	
	else if(length > MAX_LEN) /*too longer*/
		return 0;
	
	else if(isKeyword(name)) /*a keyword*/
		return 0;
	
	else if(name[0] < 'A' || name[0] > 'z' || (name[0] > 'Z' && name[0] < 'a')) /*the first charecter isn't a letter*/
		return 0;
	
	for(i = 0; i < length; i++)/*go forward in the word*/
		if(name[i] < 'A' || name[i] > 'z' || (name[i] > 'Z' && name[i] < 'a')) /*not a letter*/
			if(name[i] < '0' || name[i] > '9')/*not a number*/
				return 0;
	
	return 1;/*legal name*/
}

int ifExtern(char* name){
	symbolTable *temp = head;
	
	while(temp != NULL){ /*the symbol-table not end*/
		if(strcmp(temp->name, name) == 0) /*it's the symbol*/
			return temp->isExtern;
		temp = temp->next;/*go to the next symbol*/
	}
	
	return 0; /*not in the sumbol table*/
}

int externSymbol(char* name, int numLine){
	if(search(name) == EOF){ /*the symbol not in the symbol-table yet*/
		if(legalName(name)) /*legal name to symbol*/
			addSymbol(name, EXTERN_VAL, "extern");
		else{ /*wrong name to symbol*/
			printf("In line: %d, the symbol's name '%s' is illegal.\n", numLine, name);
			return 0;
		}	
	}
	
	else{ /*the symbol in the symbol-table*/
		if(ifExtern(name) == 0){ /*defined before in this file*/
			printf("In line: %d, symbol can't be external if it is defined in this file.\n", numLine);
			return 0;
		}
	}
	
	return 1;
}

void updateVal(int icf){
	symbolTable *temp = head;
	
	while(temp != NULL){ /*the symbol-table not end*/
		if(temp->isData) /*data attribute*/
			temp->value += icf + MIN_IC; /*add entry attribute*/

		temp = temp->next;/*go to the next symbol*/
	}
}

int entrySymbol(char* line, int numLine){
	symbolTable *temp = head;
	int length = frsWordLen(line);
	char *symbol = (char*)malloc(sizeof(char)*length);
	
	if(symbol == NULL){
		printf("Memory allocation problem, ending program.\n");
		exit(1);
	}
	
	sscanf(line, "%s", symbol); /*the symbol*/
	
	if(search(symbol) == EOF){/*the symbol isn't defined*/
		printf("In line: %d, the symbol '%s' is not defined in the file.\n", numLine, symbol);
		return 0;
	}
	
	else if(ifExtern(symbol) == 1){/*it's extern symbol*/
		printf("In line: %d, symbol cann't be external and entry.\n", numLine);
		return 0;
	}
	
	else{ /*it's legal symbol*/
		/*add entry attribute to the symbol: */
		while(temp != NULL){ /*the symbol-table not end*/
			if(strcmp(temp->name, symbol) == 0){ /*it's the symbol*/
				temp->isEntry = 1; /*add extern attribute*/
				break;
			}
			temp = temp->next;/*go to the next symbol*/
		}
		return 1;
	}
}

int getVal(char* name){
	symbolTable *temp = head;
	
	while(temp != NULL){ /*the symbol-table not end*/
		if(strcmp(temp->name, name)) /*data attribute*/
			return temp->value; /*return the value*/

		temp = temp->next;/*go to the next symbol*/
	}
	
	return EOF; /*not found*/
}

void printEntries(FILE* file){
	symbolTable *temp = head;
	
	while(temp != NULL){ /*the symbol-table not end*/
		if(temp->isEntry) /*entry attribute*/
			fprintf(file, "%s %04d\n", temp->name, temp->value);

		temp = temp->next;/*go to the next symbol*/
	}
}

void endSymbol(){
	destroyFrom(head); /*destroy the symbol-table*/
}

void destroyFrom(symbolTable* symbol){
	if(symbol == NULL) /*end of symbol-table*/
		return;
	
	destroyFrom(symbol->next); /*destroy the last symbol*/
	
	free(symbol->name); /*delete symbol's name*/
	symbol->name = NULL;
	
	free(symbol); /*delete the symbol*/
	symbol = NULL;
}
