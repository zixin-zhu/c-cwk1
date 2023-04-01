#include "errorMessage.h"

int exitMessage(int code, char * filename) {
    /**print the appropriate message based on the return_code */
    switch (code) {
        case EXIT_BAD_ARGUMENT_COUNT:
            printf("ERROR: Bad Argument Count\n"); 
            return EXIT_BAD_ARGUMENT_COUNT;
        case EXIT_BAD_FILE_NAME:
            printf("ERROR: Bad File Name (%s)\n", filename);
            return EXIT_BAD_FILE_NAME;
        case EXIT_BAD_MAGICNUMBER :
            printf("ERROR: Bad Magic Number (%s)\n", filename);
            return EXIT_BAD_MAGICNUMBER;
        case EXIT_BAD_COMMENTLINE:
            printf("ERROR: Bad Comment Line (%s)\n", filename);
            return EXIT_BAD_COMMENTLINE;
        case EXIT_BAD_DIMENSIONS:
            printf("ERROR: Bad Dimensions (%s)\n", filename);
            return EXIT_BAD_DIMENSIONS;
        case EXIT_MAXGRAY_VALUE:
            printf("ERROR: Bad Max Gray Value (%s)\n", filename);
            return EXIT_MAXGRAY_VALUE;
        case EXIT_IMAGE_MALLOC_FAILED:
            printf("ERROR: Image Malloc Failed\n");
            return EXIT_IMAGE_MALLOC_FAILED;
        case EXIT_BAD_DATA:
            printf("ERROR: Bad Data (%s)\n", filename);
            return EXIT_BAD_DATA;
        case EXIT_OUTPUT_FAILED:
            printf("ERROR: Output Failed (%s)\n", filename);
            return EXIT_OUTPUT_FAILED;
        case EXIT_MISELLANEOUS:
            printf("ERROR: Miscellaneous\n");
            return EXIT_MISELLANEOUS;
        case ECHOED:
            printf("ECHOED\n");
        default:
            return EXIT_NO_ERRORS;
    }
}
