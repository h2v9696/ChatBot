CC = gcc
CFLAGS =
DEPS = ../Server/header.h
OBJ = ../Server/header.o ../Server/DB_analyst.o client.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) `mysql_config --cflags --libs` 

client: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) `mysql_config --cflags --libs` 
