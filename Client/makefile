CC = gcc
CFLAGS =
DEPS = ../Server/header.h
OBJ = ../Server/header.o client.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

client: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
