#include "reader.h"

// reader will take the given file, and pgmStruct and will populate the struct with the files data 
int reader(FILE * inputFile, PGM * pgm) {
    // sanity check input_file
    if (inputFile == NULL) {
        // return with bad filename error code
        exitMessage(EXIT_BAD_FILE_NAME,inputFile);
        return EXIT_BAD_FILE_NAME;
    }

    // default return code is exit_no_errors
    int read_return= EXIT_NO_ERRORS;

    // Read the pgm's header data
    read_return= read_header(inputFile, pgm);
    if (read_return!= EXIT_NO_ERRORS) 

    // Read the pgm's image data
    read_return= read_imageData(inputFile, pgm);

    return read_return;
}


/**************************************     Read header     **************************************/

/* read header data of a pgm image file**/

int read_header(FILE * inputFile, PGM * pgm) {
    int read_return = EXIT_NO_ERRORS;

    read_return = read_magicNumber(inputFile, pgm);
    if (read_return != EXIT_NO_ERRORS) {
        return read_return;
    }

    read_return = read_commentLines(inputFile, pgm);
    if (read_return != EXIT_NO_ERRORS) {
        return read_return;
    }
	/* scan whitespace if present            */
    fscanf(inputFile, " ");

    read_return = read_maxGray(inputFile, pgm);
    if (read_return != EXIT_NO_ERRORS) {
        return read_return;
    }

    return EXIT_NO_ERRORS;
}


/***************************************       read magic number          ******************************************/


// read magic number expects a file pointer the start of the pgm file and a pgm struct with adiquate memory added to it
int read_magicNumber(FILE * inputFile, PGM * pgm) {

    unsigned char magic_number[2] = {'0', '0'}; 
    unsigned short *magic_Number = (unsigned short *) magic_number;
    
    /* read in the magic number **/
    magic_number[0] = getc(inputFile);
    magic_number[1] = getc(inputFile);
    
    
    /* sanity check on the magic number      */
    if (magic_number[0] == 'P' && magic_number[1] == MAGIC_NUMBER_ASCII_PGM) {
        pgm->format = 'P';

    } else { 
        /* print an error message */
        exitMessage(EXIT_BAD_MAGICNUMBER,inputFile);
        /* and return                    */
        return EXIT_BAD_MAGICNUMBER;
    }
    
    /* scan whitespace if present            */
    char whitespace[] = {' ', '\n', '\t', '\v', '\f', '\r'};
    unsigned char buffer = getc(inputFile);
    // validate buffer is white space
    for (int i = 0; i < sizeof(whitespace); i++)
    {
        if (buffer != whitespace[i])
        {
          // no space was found after the magic number, therefore return bad magic number error
            exitMessage(EXIT_BAD_MAGICNUMBER,inputFile);
            return EXIT_BAD_MAGICNUMBER;
        }
    }

    return EXIT_NO_ERRORS;
}


/******************************************      read comment line       ****************************************/


	/*  store ONE comment	         */
	char *commentLine = NULL;

    int read_commentLine(FILE *inputFile, PGM *pgm)
    {
        /**set the pgm's commentLine to null  **/ 
        pgm->commentLine = NULL;

	     /* check for a comment line              */
        char nextChar = fgetc(inputFile);
        if (nextChar == '#')
        {
            /* comment line                */
		/* allocate buffer               */
            if (pgm->commentLine != NULL)
                free(pgm->commentLine);
            // allocate memory for the comment line
            pgm->commentLine = (char *)malloc(MAX_COMMENT_LINE_LENGTH);
            if (pgm->commentLine == NULL)
            { /** malloc failed*/
                /** free memory*/
                free(pgm->commentLine);
                /* Return */
                exitMessage(EXIT_MISELLANEOUS,inputFile);
                return EXIT_MISELLANEOUS;
            }

		    char *commentString = fgets(pgm->commentLine, MAX_COMMENT_LINE_LENGTH, inputFile);
		    /* NULL means failure            */
		    if (commentString == NULL)
		    { /* NULL comment read   */
			/* free memory           */
			    free(pgm->commentLine);
			/* print an error message */
			    exitMessage(EXIT_BAD_COMMENTLINE,inputFile);
			/* and return            */
			return EXIT_BAD_COMMENTLINE;
		} /* NULL comment read   */
        }
        else
        {  /* not a comment line */
		/* put character back            */
            pgm->commentLine = NULL;
            ungetc(nextChar, inputFile);
        }

        return EXIT_NO_ERRORS;
    }

/********************************          read max gray         ****************************************/


	unsigned int width = 0, height = 0;

	/* maximum gray value (assumed)	         */
	/* make it an integer for ease	         */
	unsigned int maxGray = 255;
 
    int read_maxGray(FILE * inputFile, PGM * pgm) {
	/* read in width, height, grays          */
	/* whitespace to skip blanks             */
    int scanCount = fscanf(inputFile, " %u %u", &(pgm->width), &(pgm->height));
    if ( 
        (scanCount != 2 ) ||
        (pgm->width < MIN_IMAGE_DIMENSION) ||
        (pgm->width > MAX_IMAGE_DIMENSION) ||
        (pgm->height < MIN_IMAGE_DIMENSION) ||
        (pgm->height > MAX_IMAGE_DIMENSION) 
    ) { /* failed size sanity check    */
		/* free up the memory            */
        exitMessage(EXIT_BAD_DIMENSIONS,inputFile);
        return EXIT_BAD_DIMENSIONS;
    }
    
    /**  check the comment line **/
    int read_return= read_commentLine(inputFile, pgm);
    if (read_return!= EXIT_NO_ERRORS)                
            return read_return;
        
    /* verify max gray value**/
    scanCount = fscanf(inputFile, " %u", &(pgm->maxGray));
    if ( /* sanity check	                 */
        (scanCount != 1 ) ||
        (pgm->maxGray  !=  PGM_GRAY_VALUE) 
    ) { 
        /* Return **/
        exitMessage(EXIT_MAXGRAY_VALUE,inputFile);
        return EXIT_MAXGRAY_VALUE;
    } 


    return EXIT_NO_ERRORS;
}






/******************                  read image data      ************************************/

// this attempts to read the image data from a pgm file
int read_imageData(FILE * inputFile, PGM * pgm) {
    int read_return= EXIT_NO_ERRORS;
    /*** allocate memory to the pgm struct's image data ***/
    pgm->imageData = NULL;
    pgm->imageData = (unsigned char **) malloc(pgm->height * sizeof(unsigned char *));
    /***check the memory allocation*/ 
    if (pgm->imageData == NULL) { 
        /** Return **/
        exitMessage(EXIT_IMAGE_MALLOC_FAILED,inputFile);
        return EXIT_IMAGE_MALLOC_FAILED;
    }
    for (int i = 0; i < pgm->height; i++) {
        pgm->imageData[i] = (unsigned char *) malloc(pgm->width * sizeof(unsigned char *));
        /** check memory allocation**/
        if (pgm->imageData[i] == NULL) {
            /** return **/
            exitMessage(EXIT_IMAGE_MALLOC_FAILED,inputFile);
            return EXIT_IMAGE_MALLOC_FAILED;
        }
    }

	long nImageBytes = pgm->width * pgm->height * sizeof(unsigned char);
	/* pointer for efficient read code       */
	for (unsigned char *nextGrayValue = pgm->imageData; nextGrayValue < pgm->imageData + nImageBytes; nextGrayValue++)
	{ /* per gray value */
		/* read next value               */
		int grayValue = -1;
		int scanCount = fscanf(inputFile, " %u", &grayValue);

		/* sanity check	                 */
		if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{ /* fscanf failed */
			/* free memory           */
			free(pgm->imageData);	

			/* print error message   */
			exitMessage(EXIT_BAD_DATA,inputFile);

			/* and return            */
			return EXIT_BAD_DATA;
		} /* fscanf failed */

		/* set the pixel value           */
		*nextGrayValue = (unsigned char) grayValue;
	} /* per gray value */

    return EXIT_NO_ERRORS;
}
