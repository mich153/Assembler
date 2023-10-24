/*Saving and update the data-counter and the functions help to perform the guidance line
The functions enable to work with guidance*/

#define MIN_DC 0
/*the minimum of data-counter*/

#define MIN_STR_PRM 2
/*the minimum string parameter length - the charecter " start and finish the parameter*/

void startGuidance();/*start the work with guidance*/

int doGuidanceLine(char*, int);/*get command line and line's number, report about errors in the line and update the data-counter, 
if it extern guidance add the symbol to the symbol-table, return 0 if was error and 1 if not*/

int data(char*, int);/*get list of parameters from data-guidance line and line's number, update the data-counter and report about errors,
return 1 if it's legal list and 0 if not*/

int string(char*, int);/*get line with parameter from string-guidance line and line's number, update the data-counter and report about errors,
return 1 if it's legal parameter and 0 if not*/

int entry(char*, int);/*get line with parameter from entry-guidance line and line's number, report about errors,
and return 1 if it's legal parameter and 0 if not*/

int external(char*, int);/*get line with parameter from extern-guidance line and line's number, 
report about errors and add the symbol to symbol-table, and return 1 if it's legal parameter and 0 if not*/

int printImgData(FILE*, char*, char*, int);/*get pointer to file, the guidance, the list of operands and the address of the memory, print to the file the image machine data for all of the words from the guidance line in format to object file, return the new address*/
