#include "readFile.h"


int read_file(char * filename, PGM * pgm) {
    
    FILE * inputFile = fopen(filename, "r");                 
    if (inputFile == NULL) { 
        /**** fopen failed***/ 
        exitMessage(EXIT_BAD_FILE_NAME,inputFile);
        return EXIT_BAD_FILE_NAME;
    }

    int read_return = EXIT_NO_ERRORS;
    /*** put the data into the the pgm struct**/
    read_return = reader(inputFile, pgm);
    /*** close the file***/
    fclose(inputFile);
    /******* return ******/
    return read_return;
}