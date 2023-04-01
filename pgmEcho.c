/***********************************/
/* XJCO 1921M Programming Project  */
/* 2022-23 Spring Semester         */
/*           			   */
/*                                 */
/* Version 0.2: Zheng Wang         */
/* Version 0.1: Hamish Carr        */
/***********************************/

/***********************************/
/* A first iteration to take a pgm */
/* file in ASCII and echo the data */
/***********************************/

/***********************************/
/* Main Routine                    */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

#include "errorCode.h"

#include "pgmStruct.h"



/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/
int main(int argc, char **argv)
{ /* main() */
	/* check for correct number of arguments */
	if (argc != 3)	
	{ /* wrong arg count */
		/* print an error message        */
		printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
		/* and return an error code      */
		return EXIT_BAD_ARGUMENT_COUNT;
	} /* wrong arg count */
	if (argc == 1)
	{/*no wrong*/
	   /*return without error and print the successful message*/
		printf(USAGE_FORMAT_STRING, argv[0]);
		return EXIT_NO_ERRORS;
	}

    /* the struct will be what stores the pgm file's data**/
    PGM * pgm = (PGM * ) malloc(sizeof(PGM));
    // verify that the memory was allocated correctly
    if (pgm == NULL) // malloc failed so return malloc error code and message
	    return exitMessage(EXIT_IMAGE_MALLOC_FAILED, NULL);

    /*get the data from the file into the the pgm struct**/
    int read_return = read_file(argv[1], pgm);
	int write_return;
    if (read_return == EXIT_NO_ERRORS) 
	/* copy the data to the output file**/
	write_return = write_tofile(argv[2], pgm);
    /*return correct code with a message:**/
    if (write_return == EXIT_OUTPUT_FAILED) 
        return exitMessage(write_return, argv[2]);
    /* if the return code is exit no erros**/
    int return_code = write_return == EXIT_NO_ERRORS ? ECHOED : write_return; 
    return exitMessage(return_code, argv[1]);
}








	/* variables for storing the image       */
	/* this is NOT good modularisation       */
	/* and you will eventually replace it    */
	/* for now, leave it here                */

	/* the magic number		         */
	/* stored as two bytes to avoid	         */
	/* problems with endianness	         */
	/* Raw:    0x5035 or P5		         */
	/* ASCII:  0x5032 or P2		         */




