CC = gcc
LFLAGS = -Wall
CFLAGS = -Wall -c
OBJS = read_write_ops.o errors_warnings.o fileutil.o

fileutil: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o fileutil

read_write_ops.o: read_write_ops.c read_write_ops.h errors_warnings.h
	$(CC) $(CFLAGS) read_write_ops.c

errors_warnings.o: errors_warnings.c errors_warnings.h
	$(CC) $(CFLAGS) errors_warnings.c

fileutil.o: fileutil.c errors_warnings.h read_write_ops.h
	$(CC) $(CFLAGS) fileutil.c