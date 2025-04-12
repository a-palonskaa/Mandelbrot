#ifndef SDL_INTERPRET_H
#define SDL_INTERPRET_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define X_SIZE 780
#define Y_SIZE 780

SDL_Color color_from_int(int n);
bool drow_mandelbrot_figure(SDL_Color* colors);
bool SDL_Ctor(SDL_Window** window, SDL_Renderer** renderer);

#endif /* SDL_INTERPRET_H */
