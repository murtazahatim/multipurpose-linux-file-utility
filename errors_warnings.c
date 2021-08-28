/*
 * Developed By: Murtaza Hatim Rangwala
 * Student ID: 29861128
 * Start Date: 26th August 2021
 * Last Updated: 26th August 2021
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "errors_warnings.h"

static const char * errorMessages[] = {
        [FILE_OPEN_ERROR_INPUT] = "ERROR: The program encountered an error in opening the input file\n",
        [FILE_ALREADY_OPEN] = "ERROR: Cannot write to file that is also being read. Please choose a different directory for the output file\n",
        [ARG_FORMAT_ERROR] = "ERROR: Argument format is incorrect\n",
        [NUMBER_OF_LINES_NEGATIVE] = "ERROR: Number of Lines to print cannot be negative\n",
        [ARGUMENT_EMPTY_N] = "ERROR: There should be an argument after the -n flag\n",
        [ARGUMENT_EMPTY_D] = "ERROR: There should be an argument after the -d flag\n",
        [ARGUMENT_INVALID_N] = "ERROR: Argument for -n is not a valid number\n",
        [ARGUMENT_INVALID_D] = "ERROR: Immediately after -d, a directory path is expected\n"
};

static const char * warningMessages[] = {
        [INPUT_FILE_EMPTY] = "WARNING: Input file empty. Nothing to read.\n"
};

/**
 * This function writes error message to standard error stream and exits with code 1
 * @param errorType Type of error (enum)
 */
void throwError(enum errorTypes errorType) {
    write(2, errorMessages[errorType], strlen(errorMessages[errorType]));
    exit(1);
}

/**
 * This function writes a warning to standard output stream and exits with code 0
 * @param warningType Type of warning (enum)
 */
void throwWarning(enum warningTypes warningType) {
    write(1, warningMessages[warningType], strlen(warningMessages[warningType]));
    exit(0);
}