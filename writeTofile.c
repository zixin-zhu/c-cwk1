#include "writeTofile.h"

int write_tofile(char * filename, PGM * pgm) {
	/* open a file for writing               */
    FILE * outputFile = fopen(filename, "w");
    /* check whether file opening worked     */ 
    if (outputFile == NULL) { 
	    /*return**/
    	exitMessage(EXIT_OUTPUT_FAILED,outputFile);
        return EXIT_OUTPUT_FAILED;
    }
		
    int write_return = EXIT_NO_ERRORS;
    /**** write the read data to the given output file**/
    write_return = writer(outputFile, pgm);
    /* close the file**/
    fclose(outputFile);
    /** return */
    return write_return;
}
