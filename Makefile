CC=gcc
# CFLAGS will be the options passed to the compiler.
CFLAGS=-c -Wall -g -pthread
SRC = myshell.c utils.c parser.c commands/clear.c env.c commands/echo.c commands/help.c

OBJECTS = $(SRC:.c=.o)


all:prog

prog:$(OBJECTS) $(SRC)
	$(CC) $(OBJECTS) -o MyShell
	
%.o: %.c
	$(CC) $(CFLAGS) -c  $< -o $@ 

clean:
	rm -f $(OBJECTS)
