/*The function help to analyze a syntactic structer of a line and perform the line*/

#define MAX_LINE_LEN 81
/*the maximum charecter that can be in a line*/

#define ERROR 0
/*error in the file*/

#define LEGAL 1
/*legal file*/

int lineAnalys(char*, int); /*get line and its number, analyze syntactic and perform the line, report to the standard input about errors, 
return 0 if there is error in the line, 1 if not*/

char* skipWhitespaces(char*); /*get line and skip above whitespaces from the line (without '\n'), return the line or NULL if end of line*/

int frsWordLen(char*); /*get line and return the length of the first word (include '\0') from the line*/

int inWord(char); /*get a charecter and return 1 if it is in a word (from a file) and 0 if isn't (if it's whitespaces or EOF)*/

char* commaToSpace(char*);/*get line and change all of the commas to spaces, return the line*/

int errorList(char*, int); /*get list and list's number, report about errors in the syntactic structer of the list, 
return 1 if it's legal list and 0 if not*/

int entAndExt(char*, int); /*get line and its number, if there is entry-guidance line or used external symbol so return 1 if they defined in this file, or 0 if not, return EOF if there isn't extern symbol or there isn't entry-guidance*/
