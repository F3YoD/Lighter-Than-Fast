# Lighter Than Fast: Unknow Within

"Programmation nécessaire" project; Université de Lorraine, 2017.

This repo will contain the source for a C program, aiming to be a SDL game inspired by Faster Than Light.

## Dependencies
You need SDL2, SDL2 Image and SDL2 TTF.

- On Debian-based distros
```sh
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```
- On macOS (with [http://brew.sh/](Homebrew))
```sh
brew install sdl2 sdl2_image sdl2_ttf
```

## Build
```sh
cd src/  # Optional
make     # `make debug` to get a more talkative (through stdout) binary
```

## Goals
- Efficient memory management
- Allow to add and modify content easily through text files and image files
- Use `sdl2` for interface

## Non-Goals
- Relying too much on [FTL](http://subsetgames.com/): we're driven towards spaceships combats and ressources management, and the way we see it might evolve through time

## Optional
- Multiple language support

## Description
- You play a spaceship desparately crawling through the universe. You lack ressources and need to fight hostile vessels to steal *plasma*, a form of energy used to fuel weapons and engines

## Technical side
- We're using the `extern` keyword on two types of variables: the renderer and the fonts. We want both to stay in memory and to be accessible everywhere given the need to use them everywhere.
- Macros have been defined in order to be able to use the `#variable` notation to assert the good creation of SDL elements.

## Data structure
We define game entities such as ships, as types.
- Ships are simple structures, holding values like health points or amount of plasma. The player will go through a map, offering several options. The map is actually only a 2-dimentional array of pointers to the ships.
```c
typedef struct
{
    char name[50];
    int is_shop; // actually a boolean, kept as an integer for fscanf
    int health, shield;
    struct belongings belongings;
    int damage_min, damage_max;
    float dodge_score;
    char img_path[50];
} ship_t, *map_node_t, **map_col_t, ***map_t;
```
- Ships are defined from an external file of comma-separated values. In order to load them and shuffle them and generate the map, linked lists are used.
```c
typedef struct node
{
    void *value;
    struct node *next;
} node_t, *list_t;
```
