/*
 * Developed By: Murtaza Hatim Rangwala
 * Student ID: 29861128
 * Start Date: 19th August 2021
 * Last Updated: 21st August 2021
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Declaring an enum for different errors and an array for their messages
enum errorTypes {
    FILE_OPEN_ERROR_INPUT,
    FILE_OPEN_ERROR_OUTPUT,
    ARG_FORMAT_ERROR
};

static const char * errorMessages[] = {
    [FILE_OPEN_ERROR_INPUT] = "ERROR: The program encountered an error in opening the input file\n",
    [FILE_OPEN_ERROR_OUTPUT] = "ERROR: The program encountered an error in opening the output file\n",
    [ARG_FORMAT_ERROR] = "ERROR: Argument format is incorrect\n"
};

// Function Prototypes
void writeFromInputFileToOutputFile(int numberOfLines, int infile, int outfile);
void writeFromInputFileToStdOut(int numberOfLines, int infile);
void throwError(enum errorTypes errorType);
char* formatOutputFileName(char* outputDir, char* inputFilePath);

// Main Function
int main(int argc, char *argv[]) {

    // Assigning 250 bytes to inputFilename and outputFilename variables
    char *inputFilename = (char *) malloc(sizeof(char) * 250), *outputFilename = (char *) malloc(sizeof(char) * 250);

    // Declaring input and output file variables
    int infile, outfile = 1, numberOfLines = 10;

    // Boolean to check if text needs to be written to a different file or displayed in the terminal
    bool writeToFile = false;

    /* Since input file argument is always first, it can directly be assigned to the inputFilename variable:
       If inputFilename is passed as an argument, assign that. Otherwise, assign "sample.txt" */
    if (argc >= 2 && (strcmp(argv[1], "-d") || strcmp(argv[1], "-n"))) {
        strcpy(inputFilename, argv[1]);
    }
    else {
        strcpy(inputFilename, "sample.txt");
    }

    // Getting output directory and number of lines to read from the input file from arguments
    for(int argInd = 1; argInd < argc; argInd++) {
        if (!strcmp(argv[argInd], "-d")) {
            strcpy(outputFilename, formatOutputFileName(argv[argInd + 1], inputFilename));
            writeToFile = true;
        }
        if (!strcmp(argv[argInd], "-n")) {
            numberOfLines = atoi(argv[argInd + 1]);
        }
    }

    // Opening the input file
    if ((infile = open(inputFilename, O_RDONLY)) < 0) {
        throwError(FILE_OPEN_ERROR_INPUT);
    }

    // Free the inputFileName pointer
    free(inputFilename);

    if (writeToFile) {

        // Opening the output file
        if ((outfile = open(outputFilename, O_WRONLY | O_TRUNC | O_CREAT, 0664)) < 0) {
            throwError(FILE_OPEN_ERROR_OUTPUT);
        }

        // Free the outputFileName pointer
        free(outputFilename);

        writeFromInputFileToOutputFile(numberOfLines, infile, outfile);
    }
    else {
        writeFromInputFileToStdOut(numberOfLines, infile);
    }

    return 0;
}

// Supplementary Functions
void writeFromInputFileToOutputFile(int numberOfLines, int infile, int outfile) {

    int bytesRead, lineCounter = 0, endIndex = 0;
    char buff[1024];

    while ((bytesRead = read(infile, buff, sizeof(buff)))) {
        for(int ind = 0; ind < strlen(buff); ind++) {
            if (buff[ind] == '\n') {
                lineCounter += 1;
            }
            if (lineCounter == numberOfLines) {
                endIndex = ind;
                break;
            }
        }

        if (lineCounter < numberOfLines) {
            write(outfile, buff, bytesRead);
        }
        else {
            char *partialBuffer = malloc(endIndex + 1);
            strncpy(partialBuffer, buff, endIndex + 1);

            write(outfile, partialBuffer, endIndex + 1);

            free(partialBuffer);
            break;
        }
    }

    close(infile);
}

void writeFromInputFileToStdOut(int numberOfLines, int infile) {
    writeFromInputFileToOutputFile(numberOfLines, infile, 1);
}

void throwError(enum errorTypes errorType) {
    write(2, errorMessages[errorType], strlen(errorMessages[errorType]));
    exit(1);
}

char* formatOutputFileName(char* outputDir, char* inputFilePath) {

    char *outputFilePath = (char *) malloc(sizeof(char) * 50), *outputFileName = (char *) malloc(sizeof(char) * 50);
    int counter = strlen(inputFilePath) - 1;

    strcpy(outputFilePath, outputDir);

    if(outputFilePath[strlen(outputFilePath) - 1] != '/') {
        strcat(outputFilePath, "/");
    }

    do {
        char *tempString = (char *) malloc(sizeof(char) * 50);
        strncat(tempString, inputFilePath + counter, 1);
        strcat(tempString, outputFileName);
        strcpy(outputFileName, tempString);
        free(tempString);
        counter -= 1;
    } while (*(inputFilePath + counter) != '/');

    strcat(outputFilePath, outputFileName);

    return outputFilePath;
}

