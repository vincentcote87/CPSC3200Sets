# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -std=c++11


OBJECTS = 305 409 10055 10420 10189 10415 11947

.PHONY: all

all:
	$(OBJECTS)

$(OBJECTS): %:%.cpp

clean:
	rm -f $(OBJECTS)