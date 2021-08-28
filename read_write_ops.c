/*
 * Developed By: Murtaza Hatim Rangwala
 * Student ID: 29861128
 * Start Date: 26th August 2021
 * Last Updated: 26th August 2021
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "read_write_ops.h"
#include "errors_warnings.h"

/**
 * This function reads from input file and writes to an output file
 * @param numberOfLines number of lines to read from input file
 * @param isTailCommand start read operation from the back if true, else start from front
 * @param infile input file (integer)
 * @param outfile output file (integer)
 */
void writeFromInputFileToOutputFile(int numberOfLines, bool isTailCommand, int infile, int outfile) {
    // If it is a tail command, call readFromTailAndWrite(). Else, call readFromHeadAndWrite()
    isTailCommand ? readFromTailAndWrite(numberOfLines, infile, outfile): readFromHeadAndWrite(numberOfLines, infile, outfile);
}

/**
 * This function reads from the input file and write to standard output
 * @param numberOfLines number of lines to read from input file
 * @param isTailCommand start read operation from the back if true, else start from the front
 * @param infile input file (integer)
 */
void writeFromInputFileToStdOut(int numberOfLines, bool isTailCommand, int infile) {
    // Since default arguments are not a part of C, a proxy function is used
    writeFromInputFileToOutputFile(numberOfLines, isTailCommand, infile, 1);
}

/**
 * This function reads a fixed number of lines from the input file and writes it to the output file
 * @param numberOfLines number of lines to read and write
 * @param infile input file code (integer)
 * @param outfile output file code (integer)
 */
void readFromHeadAndWrite(int numberOfLines, int infile, int outfile) {
    int bytesRead, lineCounter = 0, endIndex = 0;

    // Total input file size (in bytes)
    off_t totalBytesInput = lseek(infile, 0L, SEEK_END);

    // Initializing a buffer of 50 bytes
    char buff[50];

    totalBytesInput < 1 ? throwWarning(INPUT_FILE_EMPTY) : lseek(infile, 0L, SEEK_SET);

    // Read 50 bytes from the input file until end is reached
    while ((bytesRead = read(infile, buff, sizeof(buff)))) {

        // Looping through the 50 byte buffer to count the number of new line characters
        for(int ind = 0; ind < strlen(buff); ind++) {
            if (buff[ind] == '\n') {
                lineCounter += 1;
            }

            /* If the buffer in this iteration contains the new line character that fulfils the numberOfLines
             * requirement, record index and break from for loop */
            if (lineCounter == numberOfLines) {
                endIndex = ind;
                break;
            }
        }

        /* If buffer was not partially interrupted due to line limit, write the entire buffer to output file. Else,
         * write the partial buffer to output based on recorded termination index */
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

    // Closing opened files
    close(infile);
    close(outfile);
}

/**
 * This function reads a fixed number of lines from the input file (starting backwards) and writes it to the output file
 * @param numberOfLines number of lines to read and write
 * @param infile input file code (integer)
 * @param outfile output file code (integer)
 */
void readFromTailAndWrite(int numberOfLines, int infile, int outfile) {
    // Counts the number of lines
    int lineCounter = 0;

    // Total input file size (in bytes)
    off_t totalBytesInput = lseek(infile, 0L, SEEK_END);

    // Allocating a single character buffer and tailOutput to assign the read data to a variable before write
    char buff[1], *tailOutput = (char *) malloc(sizeof(char) * 15000);

    // If input file empty, throw warning and exit program. Else, seek last char of file
    totalBytesInput < sizeof(buff) ? throwWarning(INPUT_FILE_EMPTY) :
    lseek(infile, (long) (totalBytesInput - sizeof(buff)), SEEK_SET);

    // Loop through all characters in input file
    for(int i = 1; i <= totalBytesInput; i++) {
        read(infile, buff, sizeof(buff));

        // If character is newline, increase counter
        if (buff[0] == '\n') {
            lineCounter += 1;
        }

        // If number of lines reached, break from loop
        if (lineCounter == numberOfLines + 1) {
            break;
        }

        // Add read character to the beginning of tailOutput
        memmove(tailOutput + 1, tailOutput, strlen(tailOutput) + 1);
        *tailOutput = buff[0];

        // Seek to next read character
        lseek(infile, (long) (totalBytesInput - (i + 1)), SEEK_SET);
    }

    // Write tailOutput to output file
    write(outfile, tailOutput, strlen(tailOutput));
    free(tailOutput);

    // Closing opened files
    close(infile);
    close(outfile);
}