/* Make object, entries and external files for a source file in assemblly.
Assume that there aren't errors in the source file*/

void makeOutput(FILE*, char*, int); /*get file, its name (without ending) and the numbers of file's line,
make and initialize output file: object, entries and external files*/

FILE* openFiles(char*, char*); /*get file's name and its ending, return pointer to the respectively empty file to write only*/

char* fullName(char*, char*); /*get file's name and its ending, return NULL if wrong ending or if there isn't name of file, 
else return the full file's name - do free is user responsibility*/
