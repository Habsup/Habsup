CC=gcc
CFLAGS=-I.
DEPS = habsup.h
OBJ = habsup.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

habsup: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
