/*
 * Developed By: Murtaza Hatim Rangwala
 * Student ID: 29861128
 * Start Date: 19th August 2021
 * Last Updated: 26th August 2021
*/

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errors_warnings.h"
#include "read_write_ops.h"
#define DEFAULT_INPUT_FILE "sample.txt"

// Function Prototypes
void formatOutputFileName(char* outputDir, char* inputFilePath, char* outputFilePath);

// Main Function
int main(int argc, char *argv[]) {

    // Assigning 250 bytes to inputFilename and outputFilename variables
    char *inputFilename = (char *) malloc(sizeof(char) * 250), *outputFilename = (char *) malloc(sizeof(char) * 250);

    char *stringToIntConversionErrorPointer=NULL;

    // Declaring input and output file variables
    int infile, outfile = 1, numberOfLines = 10;

    // Boolean checks to control program flow based on argument values
    bool isWriteToFile = false, isTailCommand = false;

    /* Since input file argument is always first, it can directly be assigned to the inputFilename variable:
       If inputFilename is passed as an argument, assign that. Otherwise, assign DEFAULT_INPUT_FILE */
    (argc >= 2 && (strcmp(argv[1], "-d") && strcmp(argv[1], "-n") && strcmp(argv[1], "-L"))) ? strcpy(inputFilename, argv[1]) :
    strcpy(inputFilename, DEFAULT_INPUT_FILE);

    // Getting output directory, number of lines to read from the input file and head/tail command from arguments
    for(int argInd = 1; argInd < argc; argInd++) {
        if (!strcmp(argv[argInd], "-d")) {

            if (argInd == argc - 1) {
                throwError(ARGUMENT_EMPTY_D);
            }

            if (!strcmp(argv[argInd], "-n") || !strcmp(argv[argInd + 1], "-L")) {
                throwError(ARGUMENT_INVALID_D);
            }

            formatOutputFileName(argv[argInd + 1], inputFilename, outputFilename);
            isWriteToFile = true;
        }
        else if (!strcmp(argv[argInd], "-n")) {

            if (argInd == argc - 1) {
                throwError(ARGUMENT_EMPTY_N);
            }

            numberOfLines = (int) strtol(argv[argInd + 1], &stringToIntConversionErrorPointer, 10);

            if (*stringToIntConversionErrorPointer) {
                throwError(ARGUMENT_INVALID_N);
            }

            // If line argument provided by user is negative, throw error
            if (numberOfLines < 0) {
                throwError(NUMBER_OF_LINES_NEGATIVE);
            }
        }
        else if (!strcmp(argv[argInd], "-L")) {
            isTailCommand = true;
        }
    }

    // Opening the input file
    if ((infile = open(inputFilename, O_RDONLY)) < 0) {
        throwError(FILE_OPEN_ERROR_INPUT);
    }

    // Free the inputFileName pointer
    free(inputFilename);

    if (isWriteToFile) {

        // Opening the output file
        if ((outfile = open(outputFilename, O_WRONLY | O_TRUNC | O_CREAT, 0664)) < 0) {
            throwError(FILE_ALREADY_OPEN);
        }

        // Free the outputFileName pointer
        free(outputFilename);

        writeFromInputFileToOutputFile(numberOfLines, isTailCommand, infile, outfile);
    }
    else {
        writeFromInputFileToStdOut(numberOfLines, isTailCommand, infile);
    }

    return 0;
}

/**
 * This function generates the output file path from the output directory CLI argument and the input file name
 * @param outputDir Output Directory Absolute Path
 * @param inputFilePath Input File Absolute Path
 * @param outputFilePath a heap allocated pointer passed by the caller so that it can be freed in the caller after use
 */
void formatOutputFileName(char* outputDir, char* inputFilePath, char* outputFilePath) {

    // Assigning 50 bytes to outputFileName
    char *outputFileName = (char *) malloc(sizeof(char) * 50);

    // Setting a counter
    int counter = strlen(inputFilePath) - 1;

    // Copying the output directory path to output file path
    strcpy(outputFilePath, outputDir);

    // Adding a trailing '/' if it has not been inputted by the user
    if(outputFilePath[strlen(outputFilePath) - 1] != '/') {
        strcat(outputFilePath, "/");
    }

    // If default file is not used, use that name for input file, else use the same default file name for output file
    if (strcmp(inputFilePath, DEFAULT_INPUT_FILE)) {
        do {
            char *tempString = (char *) malloc(sizeof(char) * 50);
            strncat(tempString, inputFilePath + counter, 1);
            strcat(tempString, outputFileName);
            strcpy(outputFileName, tempString);
            free(tempString);
            counter -= 1;
        } while (*(inputFilePath + counter) != '/');
    }
    else {
        strcpy(outputFileName, inputFilePath);
    }

    strcat(outputFilePath, outputFileName);
    free(outputFileName);
}

