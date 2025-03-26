#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <assert.h>
#include "sdl_interpret.h"

const int MAX_ITERATION = 255;
const int R2_BOUNDARY = 100;
const int CYCLE_ITERATIONS_CNT = 100;
const int X_SHIFT = 400;
const float DIMENTION_COEFF = 300;

int main() {
    SDL_Color* colors = (SDL_Color*) calloc(X_SIZE * Y_SIZE, sizeof(SDL_Color));
    if (colors == nullptr) {
        return EXIT_FAILURE;
    }

    float x0 = 0 , y0 = 0, x = 0 , y = 0;
    float x2 = 0, y2 = 0, xy = 0;
    float r2 = 0;
    int n = 0;
    clock_t start = clock();

    for (int w = 0; w < CYCLE_ITERATIONS_CNT; w++) {
        for (int i = 0; i < Y_SIZE; i++) {
            y0 = ((float) i - ((float) Y_SIZE / 2)) / DIMENTION_COEFF;
            for (int j = 0; j < X_SIZE; j++) {
                x0 = ((float) j - (((float) X_SIZE + X_SHIFT)/ 2)) / DIMENTION_COEFF;
                x = x0;
                y = y0;

                n = 0;
                r2 = 0;
                for (; (n < MAX_ITERATION) && (r2 < R2_BOUNDARY); n++) {
                    x2 = x * x;
                    y2 = y * y;
                    xy = x * y;

                    x = x2 - y2 + x0;
                    y = 2 * xy + y0;

                    r2 = x * x + y * y;
                }
                colors[i * X_SIZE + j] = color_from_int(n);
            }
        }
    }

    clock_t end = clock();
    printf("time spent is %f\n", (float) (end - start) / (CLOCKS_PER_SEC * CYCLE_ITERATIONS_CNT));
    return drow_mandelbrot_figure(colors);
}
