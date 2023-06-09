/** pgm struct deffinition*/
#include "pgmStruct.h"

/** exit codes*/
#include "errorCode.h"

// get the error writer function
#include "errorMessage.h"

/***get the read from file function */
#include "readFile.h"

/** get the write to file function***/
#include "writeTofile.h"


/** library for I/O routines*/  
#include <stdio.h>

/** library for memory routines*/   
#include <stdlib.h>


#ifndef main
int main(int argc, char **argv);
int read_file(char * filename ,PGM * pgm);
int write_tofile(char * filename, PGM *pgm);
int exitMessage(int code,char * filename); 
#endif
