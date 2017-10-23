SHELL=/usr/bin/bash  # allow brace expansion

NAME=lighter_than_fast
CFLAGS=-Wall -std=c99 -g
SDLFLAGS=`sdl2-config --cflags --libs`
O=../obj
R=../ressources
F=$(R)/fonts
FONTS=$(F)"/InterUI-{Black,Bold,Medium,Regular}{,Italic}.ttf"

all: $(O) ../bin $(O)/main.o
	@mkdir -p $(O)
	gcc $(CFLAGS) -o ../bin/$(NAME) $(O)/main.o $(SDLFLAGS)

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
	bash ../get_fonts.sh

# cleaning
clean:
	@rm -rfv $(O) ../bin
