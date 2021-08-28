/*
 * Developed By: Murtaza Hatim Rangwala
 * Student ID: 29861128
 * Start Date: 26th August 2021
 * Last Updated: 26th August 2021
*/

#ifndef MULTIPURPOSE_LINUX_FILE_UTILITY_ERRORS_WARNINGS_H
#define MULTIPURPOSE_LINUX_FILE_UTILITY_ERRORS_WARNINGS_H

// Declaring an enum for different errors
enum errorTypes {
    FILE_OPEN_ERROR_INPUT,
    FILE_ALREADY_OPEN,
    ARG_FORMAT_ERROR,
    NUMBER_OF_LINES_NEGATIVE,
    ARGUMENT_EMPTY_N,
    ARGUMENT_INVALID_N,
    ARGUMENT_EMPTY_D,
    ARGUMENT_INVALID_D
};

enum warningTypes {
    INPUT_FILE_EMPTY
};

void throwError(enum errorTypes errorType);
void throwWarning(enum warningTypes warningType);

#endif //MULTIPURPOSE_LINUX_FILE_UTILITY_ERRORS_WARNINGS_H