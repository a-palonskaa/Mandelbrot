#include <assert.h>
#include "sdl_interpret.h"

#define WHITE_COLOR 255, 255, 255, 255
const uint32_t DELAY_TIME = 60000;

SDL_Color color_from_int(int n) {
    SDL_Color color = {0, 0, 128, 255};

    if (n < 150) {
        if (n > 20) {
            color.r = 0;
            color.g = 191;
            color.b = 255;
        }
        else {
            float t = (float) n / 20;
            color.r = 255 + (0 - 255) * t;
            color.g = 10 + (0 - 10) * t;
            color.b = 167 + (128 - 167) * t;
        }
    }
    return color;
}

bool drow_mandelbrot_figure(SDL_Color* colors) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Ctor(&window, &renderer)) {
        return EXIT_FAILURE;
    }

    SDL_Event e = {};
    int quit_flag = false;
    uint32_t end_time = SDL_GetTicks() + DELAY_TIME;

    while (!quit_flag) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit_flag = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, WHITE_COLOR);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < Y_SIZE; i++) {
            for (size_t j = 0; j < X_SIZE; j++) {
                SDL_Rect square = {};
                square.x = (int)(10 + j);
                square.y = (int)(10 + i);
                square.w = 1;
                square.h = 1;

                SDL_SetRenderDrawColor(renderer, colors[i * X_SIZE + j].r, colors[i * X_SIZE + j].g,
                                                 colors[i * X_SIZE + j].b, colors[i * X_SIZE + j].a);
                SDL_RenderFillRect(renderer, &square);
            }
        }

        SDL_RenderPresent(renderer);

        if (SDL_GetTicks() >= end_time) {
            break;
        }
    }

    free(colors);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

bool SDL_Ctor(SDL_Window** window, SDL_Renderer** renderer) {
    assert(window != nullptr);
    assert(renderer != nullptr);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return EXIT_FAILURE;
    }

    *window = SDL_CreateWindow("Mandelbrot set", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                                 800, 800, SDL_WINDOW_SHOWN);

    if (*window == nullptr) {
        SDL_Quit();
        return EXIT_FAILURE;
    }

   *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == nullptr) {
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
