# Lighter Than Fast: Unknow Within

"Programmation nécessaire" project; Université de Lorraine, 2017.

This repo will contain the source for a C program, aiming to be a SDL game inspired by Faster Than Light.

## Goals
- Efficient memory management
- Allow to add and modify content easily through text files and image files
- Windows compatibility 
- Use `sdl2` for interface

## Non-Goals
- Relying too much on FTL: we're driven towards spaceships combats and ressources management, and the way we see it might evolve through time

## Optional
- Multiple language support

## Description
- You play a spaceship desparately crawling through the universe. You lack ressources and need to fight hostile vessels to steal *plasma*, a form of energy used to fuel weapons and engines

## Data structure
We define game entities such as ships, as types.
- Ships are simple structures, holding values like health points or amount of plasma
- The map will be defined with a structure derived from graphs
