SHELL = /usr/bin/env bash  # Allow brace expansion TODO maybe useless
NAME = lighter_than_fast

CC = gcc
CFLAGS = -Wall -std=c99
SDLFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf
O = ../obj
B = ../bin
A = ../assets
FONTS = $(A)/fonts/Inter-UI-Regular.ttf
MIDI_EXAMPLE = $(A)/midi/1\ Space\ Cruise\ (Title).mid
OBJECTS = $(patsubst %.c, $(O)/%.o, $(wildcard *.c))
DEBUG_MARK = $(O)/.DEBUG_MARK
RELEASE_MARK = $(O)/.RELEASE_MARK


# Manage debugging
all: $(RELEASE_MARK) binary

debug: CFLAGS += -g -DDEBUG
debug: $(DEBUG_MARK) binary

$(DEBUG_MARK) $(RELEASE_MARK):
	@$(MAKE) cleanobj
	@$(MAKE) $(O)
	@touch $@


# General
binary: $(O) $(FONTS) $(MIDI_EXAMPLE) $(B) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(B)/$(NAME) $(OBJECTS) $(SDLFLAGS)


# Objects
$(O)/tools.o: tools.c
	$(CC) $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/menu.o: menu.c
	$(CC) $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/main.o: main.c $(patsubst $(O)/main.o, , $(OBJECTS))
	$(CC) $(CFLAGS) -o $@ -c $^ $(SDLFLAGS)

$(O)/%.o: %.c  # Default
	$(CC) $(CFLAGS) -o $@ -c $< $(SDLFLAGS)


# Necessary folders
$(O) $(B):
	@mkdir $@


# Download & extract fonts
$(FONTS):
	@bash ../get_ressources.sh


# Cleaning
clean:
	@rm -rf $(O) $(B) $(A)/fonts $(A)/midi

cleanobj:
	@rm -rf $(O)
