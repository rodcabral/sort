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

void load_media(struct App* app) {
    SDL_Color title_color = {0xff,0xff,0xff,255};

    TTF_Font* title_font = TTF_OpenFont("fonts/Futurette-ExtraLight.ttf", 30);

    if(!title_font) {
        fprintf(stderr, "%s\n", TTF_GetError());
        return;
    }

    SDL_Surface *title_surface = TTF_RenderText_Blended(title_font, app->current_algorithm, title_color);

    app->title_props.x = app->container.x;
    app->title_props.y = app->container.y - 40;
    app->title_props.w = title_surface->w;
    app->title_props.h = title_surface->h;

    app->title_texture = SDL_CreateTextureFromSurface(app->renderer, title_surface);

    SDL_FreeSurface(title_surface);
    TTF_CloseFont(title_font);
}

void setup(struct App* app) {
    app->is_running = init_window(app);
    
    app->current_algorithm = "Bubble Sort";

    app->container.w = CONTAINER_WIDTH;
    app->container.h = CONTAINER_HEIGHT;
    app->container.x = (WINDOW_WIDTH / 2) - (CONTAINER_WIDTH / 2);
    app->container.y = (WINDOW_HEIGHT / 2) - (CONTAINER_HEIGHT / 2);
    
    load_media(app);
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

void render(struct App* app) {
    SDL_SetRenderDrawColor(app->renderer, 0x14, 0x14, 0x13, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderCopy(app->renderer, app->title_texture, NULL, &app->title_props);
    
    SDL_SetRenderDrawColor(app->renderer, 0xff, 0xff, 0xff, 255);
    SDL_RenderDrawRect(app->renderer, &app->container);

    SDL_RenderPresent(app->renderer);
}

void clean_sdl(struct App* app) {
    SDL_DestroyTexture(app->title_texture);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
