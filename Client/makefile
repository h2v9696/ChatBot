CC = gcc
CFLAGS =
DEPS = 
OBJ = client.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

client: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
