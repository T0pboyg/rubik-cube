# Rubik's Cube Simulator

A Rubik's Cube simulation developed in C using the SDL2 library.

## Technologies
- C
- SDL2
- GCC

## Project Structure
- main.c - Application entry point and SDL2 interface
- cube.c - Cube implementation
- cube.h - Cube declarations

## Build

Requires GCC and SDL2 development libraries.

On Windows with MSYS2 MinGW:

gcc main.c cube.c -o rubiks-cube.exe -lmingw32 -lSDL2main -lSDL2

## Run

./rubiks-cube.exe
