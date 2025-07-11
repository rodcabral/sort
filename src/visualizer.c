#include "../include/visualizer.h"

void setup(App* app) {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "%s\n", SDL_GetError());
    }

    SDL_CreateWindowAndRenderer("Sort", (int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS, &app->window, &app->renderer);

    app->is_running = true;
}

void handle_input(App* app) {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_EVENT_QUIT:
            app->is_running = false;
            break;
    }
}

void render(App* app) {
    SDL_SetRenderDrawColor(app->renderer, 0x0f, 0x0f, 0x0f, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderPresent(app->renderer);
}
