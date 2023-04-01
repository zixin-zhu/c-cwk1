/** pgm struct deffinition ***/
#include "pgmStruct.h"

/********* exit codes******/
#include "errorCode.h"

/* global constants****/
#include "pgmData.h"

/******* library for I/O routines ***/     
#include <stdio.h>

/******* library for memory routines*****/     
#include <stdlib.h>


#ifndef reader
int reader(FILE * inputFile, PGM * pgm);
int read_header(FILE * inputFile, PGM * pgm);
int read_magicNumber(FILE * inputFile, PGM * pgm);
int read_commentLine(FILE * inputFile, PGM * pgm);
int read_maxGray(FILE * inputFile, PGM * pgm);
int read_imageData(FILE * inputFile, PGM * pgm);

#endif