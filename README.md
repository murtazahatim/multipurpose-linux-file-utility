![repo-size](https://img.shields.io/github/repo-size/murtazahatim/multipurpose-linux-file-utility)
[![LinkedIn](https://img.shields.io/badge/linkedin-connect-blue)](https://www.linkedin.com/in/murtaza-rangwala-889064160/)
### NAME:
fileutil - linux file utility tool
### SYNOPSIS:
./fileutil [INPUT_FILE] [OPTION].....
### DESCRIPTION:
Reads an input file and prints to standard output. If no input file is provided, reads this document by default.
If output file is provided, write to output file. Number of lines to be read can be passed as an argument as well.
### OPTIONAL ARGUMENTS:

#### -n NUM
reads and write the number of lines provided after the -n flag. Defaults to 10.

#### -d STRING
writes output to output directory provided after the -d flag instead of standard output

#### -L
reads from tail instead of head and counts number of lines backwards

###SETUP:
1. Put all the provided project files in the same directory
2. Run the command `make` in the terminal to compile the project
3. An executable called fileutil is generated
4. Run the executable in the terminal using ./fileutil
5. 
### AUTHOR:
#### Written by Murtaza Rangwala
