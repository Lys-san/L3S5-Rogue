# Folders 
SRC = src
HEADER = include
BIN = bin

# Compilation flags
CC = gcc
CFLAGS = -I$(HEADER) -Wall -ansi -lMLV -lm

# Compilation objects
CFILE = $(wildcard $(SRC)/*.c)
OBJ = $(CFILE:$(SRC)/%.c=$(BIN)/%.o)

# Executable file
EXEC = rogue

# Execution of everything
all:$(EXEC)

# Compilation of the executable file
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Compilation of the main file since he has no .h on his own
$(BIN)/main.o: $(SRC)/main.c $(HEADER)/*.h
	$(CC) -o $@ -c $< $(CFLAGS)

# Compilation of all intermediary files
$(BIN)/%.o:$(SRC)/%.c $(HEADER)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

# Remove all intermediary files
clean:
	rm -f $(BIN)/*.o;

# Remove all files created by the Makefile
mrproper: clean
	rm -f $(EXEC)
	rm -rf $(EXEC) *.dll data/
