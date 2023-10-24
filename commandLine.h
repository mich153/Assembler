/*Saving and update the instruction-counter and the functions help to perform the command line
The functions enable to work with commands*/

#define MIN_IC 100
/*the minimum of instruction-counter*/

#define NUM_OPRND_FIRST 2
/*number of the operands for the first command group*/

#define NUM_OPRND_SEC 1
/*number of the operands for the second command group*/

#define NUM_OPRND_THIRD 0
/*number of the operands for the third command group*/

#define DEST_BITS 2
/*destination addressing's bits in a word*/

void startCommand();/*start the work with commands*/

int doCommandLine(char*, int);/*get command line and line's number, report about errors in the line and update the instruction-counter
return 0 if was error or 1 if not*/

int numOperands(char*);/*get command and return the number of operands for this command, or EOF if it isn't a command*/

int oprndList(char*, char*, int);/*get list of operands, command and the number of line, check all of the operands from the list,
return 0 if there is error, or 0 if there isn't*/
 
int symbolOperand(char*, char*, int);/*get command, list of operands (with its modes addressing) and the lise's number
if the there is symbol-operand that there isn't in the symbol-table yet return 0, else return 1*/
