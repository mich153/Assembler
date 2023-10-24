#include <stdio.h>
#include <string.h>
#include "keyword.h"

int isKeyword(char* word){
	return firstCommand(word) || secondCommand(word) || thirdCommand(word) || guidance(word) || reg(word);
/*compare to all keyword option*/
}

int firstCommand(char* word){
	return !(strcmp(word, "mov") && strcmp(word, "cmp") && strcmp(word, "add") && strcmp(word, "sub") && strcmp(word, "lea"));
/*compare to command words from the first group*/
}

int secondCommand(char* word){
	return !(strcmp(word, "clr") && strcmp(word, "not") && strcmp(word, "inc") && strcmp(word, "dec") && strcmp(word, "jmp")&& 
		strcmp(word, "bne") && strcmp(word, "jsr") && strcmp(word, "red") && strcmp(word, "prn"));
/*compare to command words from the second group*/
}


int thirdCommand(char* word){
	return !(strcmp(word, "rts") && strcmp(word, "stop"));
/*compare to command words from the third group*/
}

int guidance(char* word){
	return !(strcmp(word, "data") && strcmp(word, "string") && strcmp(word, "entry") && strcmp(word, "extern"));
/*compare to guidance words*/
}

int reg(char* word){
	if(strcmp(word, "PSW") == 0)/*it's the register PSW*/
		return 1;
	
	else if(strlen(word) == 2 && word[0] == 'r' && (word[1] >= '0' && word[1] <= '7') && word[2] == '\0')/*it's a register*/
		return 1;
	
	else
		return 0;/*it isn't a register*/
}
