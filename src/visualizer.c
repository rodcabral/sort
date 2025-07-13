#include "../include/visualizer.h"

void setup(App* app) {
    srand(time(NULL));

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "%s\n", SDL_GetError());
    }

    SDL_CreateWindowAndRenderer("Sort", (int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS, &app->window, &app->renderer);

    app->container.w = CONTAINER_WIDTH;
    app->container.h = CONTAINER_HEIGHT;
    app->container.x = (WINDOW_WIDTH / 2) - (CONTAINER_WIDTH / 2);
    app->container.y = (WINDOW_HEIGHT / 2) - (CONTAINER_HEIGHT / 2);

    app->status_container.w = WINDOW_WIDTH;
    app->status_container.h = 20;
    app->status_container.x = 0;
    app->status_container.y = WINDOW_HEIGHT - app->status_container.h;

    app->is_running = true;
    app->is_paused = false;
}

void handle_input(App* app) {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_EVENT_QUIT:
            app->is_running = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch(event.key.key) {
                case SDLK_ESCAPE:
                    app->is_running = false;
                    break;
                case SDLK_SPACE:
                    if(app->is_paused) {
                        app->is_paused = false;
                    } else {
                        app->is_paused = true;
                    }
                    break;
            }
            break;
    }

    if(!app->is_running) {
        clean_sdl(app);
        exit(0);
    }
}

void render(App* app, int r) {
    SDL_SetRenderDrawColor(app->renderer, 0x0f, 0x0f, 0x0f, 255);
    SDL_RenderClear(app->renderer);

    SDL_SetRenderDrawColor(app->renderer, 0xa9, 0xb1, 0xd6, 255);
    SDL_RenderRect(app->renderer, &app->container);

    SDL_SetRenderDrawColor(app->renderer, 0x19, 0x19, 0x19, 255);
    SDL_RenderFillRect(app->renderer, &app->status_container);

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

        SDL_RenderFillRect(app->renderer, &app->lines[i].rect);
    }

    handle_input(app); 

    SDL_RenderPresent(app->renderer);
}

void clean_sdl(App* app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
