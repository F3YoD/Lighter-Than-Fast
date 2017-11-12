SHELL=/usr/bin/env bash  # Allow brace expansion

NAME=lighter_than_fast
CFLAGS=-Wall -std=c99 -g
SDLFLAGS=$(shell pkg-config --cflags --libs sdl2 sdl2_image sdl2_ttf)
O=../obj
B=../bin
A=../assets
FONTS=$(A)/fonts/Inter-UI-Regular.ttf
MIDI_EXAMPLE=$(A)/midi/1\ Space\ Cruise\ (Title).mid
OBJECTS=$(O)/alien.o $(O)/battle.o $(O)/fond.o $(O)/game.o $(O)/interface.o $(O)/jauge.o $(O)/map.o $(O)/menu.o $(O)/ships.o $(O)/tools.o

all: $(O) $(FONTS) $(MIDI_EXAMPLE) $(B) $(O)/main.o
	gcc $(CFLAGS) -o $(B)/$(NAME) $(O)/main.o $(OBJECTS) $(SDLFLAGS)

# Necessary folders
$(O):
	@mkdir $@

../bin:
	@mkdir $@

# Objects
$(O)/alien.o: alien.c alien.h
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/battle.o: battle.c $(O)/ships.o battle.h
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/game.o: game.c $(O)/alien.o $(O)/interface.o
	gcc $(CFLAGS) -o $@ -c $^ $(SDLFLAGS)

$(O)/interface.o: interface.c $(O)/jauge.o $(O)/alien.o $(O)/ships.o $(O)/fond.o
	gcc $(CFLAGS) -o $@ -c $<

$(O)/main.o: main.c $(OBJECTS)
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/%.o: %.c
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(FONTS):  # Download & extract fonts
	@bash ../get_ressources.sh

# Cleaning
clean:
	rm -rf $(O) $(B) $(A)/fonts $(A)/midi
