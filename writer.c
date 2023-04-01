#include "writer.h"

// writer will take a pointer to a pgm struct, and write this data to the given file

int writer(FILE * outputFile, PGM * pgm) {
    // return code is used to return any error codes at the end
    int write_return = EXIT_NO_ERRORS;

    // write the header data to the output file:
    write_return =  write_header(outputFile, pgm);
    if (write_return != EXIT_NO_ERRORS) 
    write_return = write_ascii(outputFile, pgm);
	return write_return;
}



/* write the header part of the file***/

int write_header(FILE * outputFile, PGM * pgm) {
   /* write magic number, size & gray value */
    size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", pgm->width, pgm->height, pgm->maxGray);

	/* check that dimensions wrote correctly */
    if (nBytesWritten <0) {
        /**Return  */
        exitMessage(EXIT_OUTPUT_FAILED,outputFile);
        return EXIT_OUTPUT_FAILED;
    } 
 
    /** return without error */
    return EXIT_NO_ERRORS;
}



int write_ascii(FILE * outputFile, PGM * pgm){
    /* pointer for efficient write code      */
    size_t nBytesWritten = 0;
	long nImageBytes = pgm->width * pgm->height * sizeof(unsigned char);
    for (unsigned char *nextGrayValue = pgm->imageData; nextGrayValue < pgm->imageData + nImageBytes; nextGrayValue++)
    { /* per gray value */
        /* get next char's column        */
        int nextCol = (nextGrayValue - pgm->imageData + 1) % pgm->width;

        /* write the entry & whitespace  */
        nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n') );

        /* sanity check on write         */
        if (nBytesWritten < 0)
        { /* data write failed   */
            break;
        } /* data write failed   */
    } /* per gray value */

    /* check for write failure         */
    if (nBytesWritten < 0)
    { /* data write failed   */
        /* print error message   */
        exitMessage(EXIT_OUTPUT_FAILED,outputFile);       	

        /* return an error code  */
        return EXIT_OUTPUT_FAILED;
    } /* data write failed   */

    /* at this point, we are done and can exit with a success code */
    return EXIT_NO_ERRORS;
} /* main() */
