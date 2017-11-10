SHELL=/usr/bin/env bash  # allow brace expansion

NAME=lighter_than_fast
CFLAGS=-Wall -std=c99 -g
SDLFLAGS=`sdl2-config --cflags --libs`
O=../obj
B=../bin
A=../assets
FONTS=$(A)"/fonts/InterUI-{Black,Bold,Medium,Regular}{,Italic}.ttf"

all: $(O) $(FONTS) $(B) $(O)/main.o
	gcc $(CFLAGS) -o $(B)/$(NAME) $(O)/main.o $(SDLFLAGS)

# necessary folders
$(O):
	mkdir $@

../bin:
	mkdir $@

# objects
$(O)/main.o: main.c $(O)/battle.o $(O)/map.o
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/battle.o: $(O)/ships.o battle.c battle.h
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(O)/%.o: %.c %.h  # for ships, shops, map
	gcc $(CFLAGS) -o $@ -c $< $(SDLFLAGS)

$(FONTS):  # download & extract fonts
	bash ../get_ressources.sh

# cleaning
clean:
	rm -rf $(O) $(B) $(A)/fonts
