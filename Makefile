#CC = i686-w64-mingw32-gcc
CC = gcc
CFLAGS = -ansi -Wall -lMLV 
LDLIBS = -lMLV -lm -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf -lSDL_gfx -lxml2 -lglib-2.0 -D SDL_MAIN_HANDLED

EXEC = test
OBJECTS = \
	src/main.o \
	src/interface.o \
	src/sound.o \
	src/colors.o \
	src/level.o \
	src/enemy.o \
	src/treasure.o \
	src/player.o \
	src/action.o \
	src/turn.o

FILES =                  \
	redistributables/data  \
	redistributables/*.dll

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJECTS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LDLIBS)

.PHONY: clean mrproper

clean:
	rm -rf $(OBJECTS)

mrproper: clean
	rm -rf $(EXEC) *.dll data/
