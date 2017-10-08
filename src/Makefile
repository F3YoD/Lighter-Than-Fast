SHELL=/bin/bash  # allow brace expansion

NAME=lighter_than_fast
CFLAGS=-Wall -std=c99 -g  # use of c11 standard for anonymous unions and unicode support
O=../obj

all: $(O) ../bin $(O)/main.o
	gcc $(CFLAGS) -o ../bin/$(NAME) $(O)/main.o

# necessary folders
$(O):
	mkdir $@

../bin:
	mkdir $@

# objects
$(O)/main.o: main.c $(O)/battle.o $(O)/map.o
	gcc $(CFLAGS) -o $@ -c $<

$(O)/battle.o: $(O)/ships.o battle.c battle.h
	gcc $(CFLAGS) -o $@ -c $<

$(O)/%.o: %.c %.h  # for ships, shops, map
	gcc $(CFLAGS) -o $@ -c $<

# cleaning
clean:
	rm -v $(O)/*
