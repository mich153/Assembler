/*Represent the symbol-table and the functions doing operation on a symbol or on the symbol-table.
The functions enable to work with symbols*/

#define MAX_LEN 31
/*the maximum length of symbol*/

#define EXTERN_VAL 0
/*the value that symbol with extern attributes get*/

typedef struct symbolTable{ /*the symbol-table*/
	char *name;
	int value; 
	int isExtern, isEntry, isData, isCode; /*if symbol's attributes is extern, entry, data or code respectively*/
	struct symbolTable *next;
}symbolTable;

void startSymbol(); /*starting the work with symbols*/

char* doSymbolDef(char*, int); /*get line with symbol definition and line's number, perform the symbol's definition and report about errors
return the symbol's name or NULL if there is problem with the name*/

char* symbolName(char*, int); /*get line that start with definition of symbol and line's number,
return the name of symbol or NULL if there is problem with the name and report them in the standard input*/

void addSymbol(char*, int, char*); /*get symbol's name and value and the attributes code or data, 
add the symbol with the parameters that get to the end of symbol-table*/

void initSymbol(symbolTable*, char*, int, char*); /*get symbol, symbol's name and value and the attributes code or data,
initialize the symbol with the parameters that get*/

int search(char*); /*get symbol's name, and return where is the symbol in the symbol-table or EOF if it isn't in the symbol-table*/

int legalName(char*); /*get name of symbol and return 1 if the name is legal name, or 0 if it isn't*/

int ifExtern(char*); /*get name of symbol, return 1 if the symbol has extern attributes or 0 if not*/

int externSymbol(char*, int); /*get symbol's name and line's number, if the symbol defined so add the attribute extern, 
else make new symbol with the value EXTERN_VAL, return 0 if there is error and report about it, else return 1*/

void updateVal(int); /*get the final instruction-counter and update the symbol's value which has data attribute*/

int entrySymbol(char*, int); /*get symbol's name and line's number, if the symbol defined (and it's not external) so add the attribute entry, 
else report about error, return 0 if there is error, else return 1*/

int getVal(char*); /*get symbol's name and return the symol's value, or EOF if it's not in the symbol-table*/

void printEntries(FILE*); /*get pointer to file and print to it list of entries symbol and them values*/

void endSymbol(); /*end the word with symbol*/

void destroyFrom(symbolTable*);
