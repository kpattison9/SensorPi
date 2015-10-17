#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC=gcc
CFLAGS = -Wall
TARGET=SensorPi

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
all: $(TARGET)

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
SensorPi:  main.o Uart.o 
	$(CC) $(CFLAGS) -o SensorPi main.o Uart.o 

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
main.o:  main.c /Periph/uart.h
	$(CC) $(CFLAGS) -c main.c

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
Uart.o:  /Periph/uart.c /Periph/uart.h 
	$(CC) $(CFLAGS) -c /Periph/uart.c


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) SensorPi *.o *~