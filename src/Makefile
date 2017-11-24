SHELL=/usr/bin/env bash  # Allow brace expansion

NAME=lighter_than_fast
CFLAGS=-Wall -std=c99 -g
SDLFLAGS=$(shell pkg-config --cflags --libs sdl2 sdl2_image sdl2_ttf)
O=../obj
B=../bin
A=../assets
FONTS=$(A)/fonts/Inter-UI-Regular.ttf
MIDI_EXAMPLE=$(A)/midi/1\ Space\ Cruise\ (Title).mid
OBJECTS=$(patsubst %.c, $(O)/%.o, $(wildcard *.c))

all: $(O) $(FONTS) $(MIDI_EXAMPLE) $(B) $(OBJECTS)
	gcc $(CFLAGS) -o $(B)/$(NAME) $(OBJECTS) $(SDLFLAGS)

# Necessary folders
$(O) $(B):
	@mkdir $@

# Objects
$(O)/alien.o: alien.c alien.h
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/battle.o: battle.c $(O)/ships.o battle.h
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/game.o: game.c $(O)/alien.o $(O)/interface.o
	gcc $(CFLAGS) -o $@ -c $^ $(SDLFLAGS)

$(O)/interface.o: interface.c $(O)/jauge.o $(O)/alien.o $(O)/ships.o $(O)/fond.o
	gcc $(CFLAGS) -o $@ -c $^ $(SDLFLAGS)

$(O)/main.o: main.c $(patsubst $(O)/main.o, , $(OBJECTS))
	gcc $(CFLAGS) -o $@ -c $^ $(SDLFLAGS)

$(O)/%.o: %.c
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(FONTS):  # Download & extract fonts
	@bash ../get_ressources.sh

# Cleaning
clean:
	rm -rf $(O) $(B) $(A)/fonts $(A)/midi
