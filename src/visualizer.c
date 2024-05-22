#include <visualizer.h>

bool init_window(struct App* app) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return false;
    }

    if(TTF_Init() < 0) {
        fprintf(stderr, "%s\n", TTF_GetError());
        return false;
    }

    app->window = SDL_CreateWindow(
        "Sort Visualizer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if(!app->window) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return false;
    }

    app->renderer = SDL_CreateRenderer(app->window, -1, SDL_RENDERER_ACCELERATED);

    if(!app->renderer) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return false;
    }

    return true;
}

void process_input(struct App* app) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                app->is_running = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        app->is_running = false;
                        break;
                }
                break;
        }
    }
}

void clean_sdl(struct App* app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
