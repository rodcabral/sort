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

void render(App* app, int r) {
    SDL_SetRenderDrawColor(app->renderer, 0x0f, 0x0f, 0x0f, 255);
    SDL_RenderClear(app->renderer);

    SDL_SetRenderDrawColor(app->renderer, 0xa9, 0xb1, 0xd6, 255);
    SDL_RenderDrawRectF(app->renderer, &app->container);

    SDL_SetRenderDrawColor(app->renderer, 0x19, 0x19, 0x19, 255);
    SDL_RenderFillRectF(app->renderer, &app->status_container);

    int gap = 1;
    
    int curr_x = app->container.x;
    for(int i = 0; i < app->length; ++i) {
        app->lines[i].rect.y = app->container.y + app->container.h;
        app->lines[i].rect.w = (app->container.w / app->length) - gap;
        app->lines[i].rect.x = curr_x;
        app->lines[i].rect.h = -(app->lines[i].value);
        
        curr_x += app->lines[i].rect.w + gap;

        if(app->is_sorted) {
            SDL_SetRenderDrawColor(app->renderer, 0x47, 0xad, 0x61, 255);
        } else if(i == r + gap){
            SDL_SetRenderDrawColor(app->renderer, 0xc3, 0x40, 0x43, 255);
        } else {
            SDL_SetRenderDrawColor(app->renderer, 0xee, 0xee, 0xee, 255);
        }

        SDL_RenderFillRectF(app->renderer, &app->lines[i].rect);
    }

    handle_input(app); 

    SDL_RenderPresent(app->renderer);
}
