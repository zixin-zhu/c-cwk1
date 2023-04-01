/** pgm struct deffinition*/
#include "pgmStruct.h"

/** exit codes*/
#include "errorCode.h"

/**get the reader function */
#include "reader.h"

/** library for I/O routines*/
#include <stdio.h>

/** library for memory routines*/
#include <stdlib.h>


int read_file(char * filename, PGM * pgm);