CC = gcc
CFLAGS =
DEPS = DB_analyst.h
OBJ = DB_analyst.o server.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) `mysql_config --cflags --libs` 

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) `mysql_config --cflags --libs` 
