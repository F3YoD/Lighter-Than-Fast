# Lighter Than Fast: Unknow Within

"Programmation nécessaire" project; Université de Lorraine, 2017.

This repo will contain the source for a C program, aiming to be a SDL game inspired by Faster Than Light.

## Goals
- Efficient memory management
- Allow to add and modify content easily through text files and image files
- Windows compatibility 
- Use `sdl2` for interface

## Non-Goals
- Relying too much on [FTL](http://subsetgames.com/): we're driven towards spaceships combats and ressources management, and the way we see it might evolve through time

## Optional
- Multiple language support

## Description
- You play a spaceship desparately crawling through the universe. You lack ressources and need to fight hostile vessels to steal *plasma*, a form of energy used to fuel weapons and engines

## Data structure
We define game entities such as ships, as types.
- Ships are simple structures, holding values like health points or amount of plasma
```c
typedef struct
{
    // A ship is identified by a name
    // Maybe some part of it should be randomly generated?
    char * name;
    // A shop is just a ship willing to trade stuff
    bool is_shop;
    // A ship has health, it is destroyed if this goes to or bellow 0
    int hp;
    // A ship has belongings onboard
    belongings_t *belongings;
    // A ship deals damage to others, with some room for randomness
    int damage_min;
    int damage_max;
    // A skilled pilot can dodge attacks
    float dodge_score;
    // Shield can reduce damages
    // Should it be extra health or constantly reduce damages?
    int shield;
    /* IDEAS */
    // int crew_size;
    // Enemy and self level, to balance gameplay, e.g. having more enemies of class X if player is class X
    // int level;
}
ship_t;
```
- The map will be defined with a structure derived from graphs
```c
typedef struct node
{
    // Either a ship or a shop in a node
    ship_t * target;
    // One node can lead to other nodes, represented as an array
    struct node * next;
}
map_node_t;

// One column of the map can be one or several nodes, stored as an array
typedef struct
{
    int nb_nodes;
    map_node_t * nodes; // Array of nodes
}
map_col_t;

// The full map is several map columns
typedef struct
{
    int nb_col;
    map_col_t * columns; // Array of columns
}
map_t;
```


Along the path, we'll adopt [CS50's Style Guide](https://manual.cs50.net/style).
