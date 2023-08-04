# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation
 
CC = g++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date

# SRCS = main.cpp
# OBJS = $(SRCS:.cpp=.o)
# EXECUTABLE = program

# .PHONY: all clean		

all: program

program: main.o
	$(CC) $(CFLAGS) main.o -o program

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

clean:
	rm -f program main.o
