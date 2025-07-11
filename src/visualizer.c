#include "../include/visualizer.h"

void setup(App* app) {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "%s\n", SDL_GetError());
    }

    SDL_CreateWindowAndRenderer("Sort", (int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS, &app->window, &app->renderer);

    app->is_running = true;
}
