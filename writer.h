// pgm struct deffinition 
#include "pgmStruct.h"

/** exit codes*/
#include "errorCode.h"

// global constants
#include "pgmData.h"

/** library for I/O routines*/      
#include <stdio.h>

/** library for memory routines*/    
#include <stdlib.h>


#ifndef writer
int writer(FILE * outputFile, PGM * pgm);
int write_header(FILE * outputFile, PGM * pgm);
int write_ascii(FILE * outputFile, PGM * pgm);
#endif