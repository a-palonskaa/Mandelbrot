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

    clock_t start = clock();
    float delta_x0 = 1 / DIMENTION_COEFF;

    for (int w = 0; w < CYCLE_ITERATIONS_CNT; w++) {
        for (int i = 0; i < Y_SIZE; i++) {
            float val_y0 = ((float) i - ((float) Y_SIZE / 2)) / DIMENTION_COEFF;
            for (int j = 0; j < X_SIZE; j += 4) {
                float val_x0 = ((float) j - (((float) X_SIZE + X_SHIFT)/ 2)) / DIMENTION_COEFF;
                float y0[4] = {val_y0, val_y0, val_y0, val_y0};
                float x0[4] = {val_x0, val_x0 + delta_x0, val_x0 + 2 * delta_x0, val_x0 + 3 * delta_x0};
                float x[4] = {}; for (int c = 0; c < 4; c++) x[c] = x0[c];
                float y[4] = {}; for (int c = 0; c < 4; c++) y[c] = y0[c];

                int N[4] = {};
                for (int n = 0; n < MAX_ITERATION; n++) {
                    float x2[4] = {}; for (int c = 0; c < 4; c++) x2[c] = x[c] * x[c];
                    float y2[4] = {}; for (int c = 0; c < 4; c++) y2[c] = y[c] * y[c];
                    float xy[4] = {}; for (int c = 0; c < 4; c++) xy[c] = x[c] * y[c];

                    for (int c = 0; c < 4; c++) x[c] = x2[c] - y2[c] + x0[c];
                    for (int c = 0; c < 4; c++) y[c] = 2 * xy[c] + y0[c];

                    float r2[4] = {}; for (int c = 0; c < 4; c++) r2[c] = x[c] * x[c] + y[c] * y[c];
                    int cmp[4] = {};
                    for (int c = 0; c < 4; c++) if (r2[c] <= R2_BOUNDARY) cmp[c] = 1;

                    int mask = 0;
                    for (int c = 0; c < 4; c++) mask |= (cmp[c] << c);
                    if (!mask) break;

                    for (int c = 0; c < 4; c++) N[c] += cmp[c];
                }
                for (int c = 0; c < 4; c++) colors[i * X_SIZE + j + c] = color_from_int(N[c]);
            }
        }
    }

    clock_t end = clock();
    printf("time spent is %f\n", (float) (end - start) / (CLOCKS_PER_SEC * CYCLE_ITERATIONS_CNT));
    return drow_mandelbrot_figure(colors);
}
