/* The program is assembler
The actions that the program performs:
-get names of assembly source files in assembly from the command line
-report to the standart input about errors for each file that has any error
-for each files that hasn't errors, the program creating object file, file with the entries symbols, and file with the externals symbols*/

/* The assumptions in the program:
-maximum length in line is 81 (with '\n')
-the names of files that get from the command line is without the ending ".as"
-only spaces separate the names of files in the command line*/

#define END_NAME_LEN 4
/*the length of ending source file (in assembly) name*/

int start(char*); /*get name of source file (without the ending ".as") and start with it the assembler work*/

int firstPass(FILE*); /*get pointer to file, pass in the first time above the file and report about errors that found, return the number of lines, or EOF if there is error in the file*/

int secondPass(FILE*); /*get pointer to file, pass in the second time above the file and report about errors that found, return 0 if there is error or 1 if not*/
