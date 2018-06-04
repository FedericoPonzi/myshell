CC=gcc
LINKER = gcc
TARGET = myshell

CFLAGS= -std=c99 -Wall -g -pthread
LFLAGS = -Wall -I. -lreadline
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/commands/*.c)
# SRC = myshell.c utils.c parser.c commands/clear.c env.c commands/echo.c commands/help.c commands./
# OUT = myshell

OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

#OBJECTS = $(SRC:.c=.o)


#all:prog

#prog:$(OBJECTS) $(SRC)
# 	$(CC) $(OBJECTS) -o myshell

##%.o: %.c
#	$(CC) $(CFLAGS) -c  $< -o $@

#clean:
#	rm -f $(OBJECTS) $(OUT)



$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"


