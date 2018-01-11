SHELL = /usr/bin/env bash
NAME = lighter_than_fast

CC = gcc
CFLAGS = -Wall -std=gnu99
SDLFLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_ttf
O = ../obj
B = ../bin
A = ../assets
EXEC = $(B)/$(NAME)
OBJECTS = $(patsubst %.c, $(O)/%.o, $(wildcard *.c))
FONTS = $(A)/fonts/firamono.ttf
DEBUG_MARKER = $(O)/.DEBUG_MARKER
RELEASE_MARKER = $(O)/.RELEASE_MARKER


# Manage debugging
all: $(RELEASE_MARKER) $(EXEC)

debug: CFLAGS += -g -DDEBUG
debug: $(DEBUG_MARKER) $(EXEC)

$(DEBUG_MARKER) $(RELEASE_MARKER):
	@$(MAKE) cleanobj
	@$(MAKE) $(O)
	@touch $@


# Run
run: $(EXEC)
	@$(EXEC)


# General
$(EXEC): $(O) $(FONTS) $(B) $(OBJECTS)
	@$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(SDLFLAGS)
	@echo "Executable file created in "$(EXEC)


# Objects
$(O)/%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<


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
	@rm $(EXEC)
