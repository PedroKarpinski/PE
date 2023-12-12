CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wvla -g

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXECUTABLE = cliente.exe
else
    RM = rm -rf
    EXECUTABLE = cliente
endif

all: bignumber.o
	$(CC) $(CFLAGS) bignumber.o client.c -o $(EXECUTABLE)

bignumber.o: bignumber.h
	$(CC) $(CFLAGS) -c bignumber.c

clean:
	$(RM) *.o $(EXECUTABLE)
