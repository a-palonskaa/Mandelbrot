#include <stdio.h>
#include <stdlib.h>
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

    float offsets[4] = {0.0, 1.0, 2.0, 3.0};
    const float32x4_t v_offsets = vld1q_f32(offsets);
    const float32x4_t v_scale = vdupq_n_f32(1.0 / DIMENTION_COEFF);

    for (int w = 0; w < CYCLE_ITERATIONS_CNT; w++) {
        for (int i = 0; i < Y_SIZE; i++) {
            float val_y0 = ((float) i - ((float) Y_SIZE / 2)) / DIMENTION_COEFF;

            for (int j = 0; j < X_SIZE; j += 4) {
                float x0_val = ((float)j - ((float)X_SIZE +  X_SHIFT) / 2) / DIMENTION_COEFF;
                float32x4_t x0 = vaddq_f32(vdupq_n_f32(x0_val),
                                           vmulq_f32(v_scale, v_offsets));
                float32x4_t y0 = vdupq_n_f32(val_y0);

                float32x4_t x = x0;
                float32x4_t y = y0;

                int32x4_t N = vdupq_n_s32(0);
                float32x4_t threshold = vdupq_n_f32(100.0);

                for (int n = 0; n < MAX_ITERATION; n++) {
                    float32x4_t x2 = vmulq_f32(x, x);
                    float32x4_t y2 = vmulq_f32(y, y);
                    float32x4_t xy = vmulq_f32(x, y);

                    x = vaddq_f32(vsubq_f32(x2, y2), x0);
                    y = vaddq_f32(vaddq_f32(xy, xy), y0);

                    float32x4_t r2 = vaddq_f32(x2, y2);
                    uint32x4_t cmp = vshrq_n_u32(vcleq_f32(r2, threshold), 31);

                    if (vaddvq_u32(cmp) == 0) break;
                    N = vaddq_s32(N, cmp);
                }

                int N_vals[4] = {};
                vst1q_s32(N_vals, N);
                for (int c = 0; c < 4; c++) {
                    colors[i * X_SIZE + j + c] = color_from_int(N_vals[c]);
                }
            }
        }
    }

    clock_t end = clock();
    printf("time spent is %f\n", (float) (end - start) / (CLOCKS_PER_SEC * CYCLE_ITERATIONS_CNT));
    return drow_mandelbrot_figure(colors);
}

