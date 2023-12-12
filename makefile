all: bignumber.o
	gcc bignumber.o client.c -o client

ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXECUTABLE = cliente.exe
else
    RM = rm -rf
    EXECUTABLE = cliente
endif

bignumber.o: bignumber.h
	gcc -c bignumber.c

clean:
	$(RM) *.o $(EXECUTABLE)