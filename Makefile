LDLIBS += -llapacke -llapack -lblas -ggdb -Og -Wall
CC = gcc

.PHONY: clean

main: main.o

clean:
	$(RM) main.o main
