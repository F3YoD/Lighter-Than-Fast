SHELL=/bin/bash  # allow brace expansion

NAME=lighter_than_fast
CFLAGS=-Wall -std=c99 -g  # use of c11 standard for anonymous unions and unicode support
SDLFLAGS=`sdl2-config --cflags --libs`
O=../obj

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

# cleaning
clean:
	@rm -rfv $(O)/
