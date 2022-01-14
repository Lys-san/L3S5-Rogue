# Folders 
SRC    = src
HEADER = include
BIN    = bin

# Compilation flags
CC = i686-w64-mingw32-gcc #gcc
CFLAGS = -I$(HEADER) -Wall -ansi -lMLV -lm

#this line for Lyly, because compiling MLV on windows
LDLIBS = -lMLV -lm -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_gfx -lxml2 -lglib-2.0 -D SDL_MAIN_HANDLED

# Compilation objects
CFILE = $(wildcard $(SRC)/*.c)
OBJ = $(CFILE:$(SRC)/%.c=$(BIN)/%.o)

# Executable file
EXEC = rogue

# for MLV compilation on windows
FILES =                  \
	redistributables/data  \
	redistributables/*.dll

# Execution of everything
all:$(EXEC)

# Compilation of the executable file
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

# Compilation of the main file since he has no .h on his own
$(BIN)/main.o: $(SRC)/main.c $(HEADER)/*.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS)

# Compilation of all intermediary files
$(BIN)/%.o:$(SRC)/%.c $(HEADER)/%.h
	$(CC) -o $@ -c $< $(CFLAGS) $(LDLIBS)

.PHONY: clean mrproper

# Remove all intermediary files
clean:
	rm -f $(BIN)/*.o;

# Remove all files created by the Makefile
mr	proper: clean
	rm -f $(EXEC)
	rm -rf $(EXEC) *.dll data/