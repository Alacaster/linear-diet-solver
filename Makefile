LDLIBS += -llapacke -llapack -lblas -ggdb -Og -Wall -std=gnu17
CC = gcc

.PHONY: clean

main: main.o

clean:
	$(RM) main.o main