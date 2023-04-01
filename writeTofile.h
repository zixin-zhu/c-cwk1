/** pgm struct deffinition*/
#include "pgmStruct.h"

/** exit codes*/
#include "errorCode.h"

/**get the writer function */
#include "writer.h"

/** library for I/O routines*/
#include <stdio.h>

/** library for memory routines*/
#include <stdlib.h>


int write_tofile(char * filename, PGM * pgm);