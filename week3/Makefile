# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -std=c++11 -Wall

OBJECTS = 501 793 11136

.PHONY: all

all:
	$(OBJECTS)

$(OBJECTS): %:%.cpp

clean:
	rm -f $(OBJECTS)