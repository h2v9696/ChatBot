CC = gcc
CFLAGS =
DEPS = 
OBJ = DB_analyst.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) `mysql_config --cflags --libs`
