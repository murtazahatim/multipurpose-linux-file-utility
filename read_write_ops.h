/*
 * Developed By: Murtaza Hatim Rangwala
 * Student ID: 29861128
 * Start Date: 26th August 2021
 * Last Updated: 26th August 2021
*/

#ifndef MULTIPURPOSE_LINUX_FILE_UTILITY_READ_WRITE_OPS_H
#define MULTIPURPOSE_LINUX_FILE_UTILITY_READ_WRITE_OPS_H

#include <stdbool.h>

void writeFromInputFileToOutputFile(int numberOfLines, bool isTailCommand, int infile, int outfile);
void writeFromInputFileToStdOut(int numberOfLines, bool isTailCommand, int infile);
void readFromHeadAndWrite(int numberOfLines, int infile, int outfile);
void readFromTailAndWrite(int numberOfLines, int infile, int outfile);

#endif //MULTIPURPOSE_LINUX_FILE_UTILITY_READ_WRITE_OPS_H
