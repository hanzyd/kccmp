# the compiler: gcc for C program, define as g++ for C++
CC = g++

CFLAGS  = -g -Wall -ggdb

TARGET = kccmp

all: config.cpp config_value.cpp config_show.cpp
	$(CC) $(CFLAGS) -o $(TARGET) config.cpp config_value.cpp config_show.cpp

clean:
	$(RM) $(TARGET)