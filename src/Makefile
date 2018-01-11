SHELL = /usr/bin/env bash
NAME = lighter_than_fast

CC = gcc
CFLAGS = -Wall -std=gnu99
SDLFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf
O = ../obj
B = ../bin
A = ../assets
FONTS = $(A)/fonts/firamono.ttf
OBJECTS = $(patsubst %.c, $(O)/%.o, $(wildcard *.c))
DEBUG_MARKER = $(O)/.DEBUG_MARKER
RELEASE_MARKER = $(O)/.RELEASE_MARKER


# Run
run:
	@$(B)/$(NAME)


# Manage debugging
all: $(RELEASE_MARKER) binary

debug: CFLAGS += -g -DDEBUG
debug: $(DEBUG_MARKER) binary

$(DEBUG_MARKER) $(RELEASE_MARKER):
	@$(MAKE) cleanobj
	@$(MAKE) $(O)
	@touch $@


# General
binary: $(O) $(FONTS) $(B) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(B)/$(NAME) $(OBJECTS) $(SDLFLAGS)
	@echo "Executable file created in "$(B)"/"$(NAME)


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
