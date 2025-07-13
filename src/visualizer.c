#include "../include/visualizer.h"

SDL_Texture* create_text(App* app, const char* text, SDL_Color color, SDL_FRect* rect, int size) {
    TTF_Font* font = TTF_OpenFont("./fonts/montserrat-regular.otf", size);

    if(!font) {
        fprintf(stderr, "Could not open font!\n");
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, strlen(text), color);

    if(!surface) {
        fprintf(stderr, "Could not create font surface!\n");
    }

    rect->w = surface->w;
    rect->h = surface->h;
    
    SDL_Texture *new_texture = SDL_CreateTextureFromSurface(app->renderer, surface);

    if(!new_texture) {
        fprintf(stderr, "Could not create font texture!\n");
    }

    SDL_DestroySurface(surface);
    TTF_CloseFont(font);

    return new_texture;
}


void load_media(App* app) {
    SDL_Color text_color = {0xc1, 0xc4, 0xdb, 255};
    SDL_Color focus_color = {0xc0, 0xa3, 0x6e, 255};
    SDL_Color paused_color = {0xc3, 0x40, 0x43, 255};

    app->title.texture = create_text(app, app->current_algorithm, text_color, &app->title.rect, 21);
    app->title.rect.x = app->container.x + (app->container.w/2) - (app->title.rect.w/2);
    app->title.rect.y = app->container.y - 50;

    char info_buffer[100];
    snprintf(info_buffer, 100, "length:  %d  |  press", app->length);

    app->info.texture = create_text(app, info_buffer, text_color, &app->info.rect, 13);
    app->info.rect.x = app->status_container.x + 10;
    app->info.rect.y = app->status_container.y + 1;

    app->pause_focus.texture = create_text(app, "  SPACE", focus_color, &app->pause_focus.rect, 11);
    app->pause_focus.rect.x = app->info.rect.x + app->info.rect.w;
    app->pause_focus.rect.y = app->status_container.y + 3;
    
    app->second_pause_info.texture = create_text(app, "  to pause", text_color, &app->second_pause_info.rect, 13);
    app->second_pause_info.rect.x = app->pause_focus.rect.x + app->pause_focus.rect.w;
    app->second_pause_info.rect.y = app->status_container.y + 1;

    app->pause_info.texture = create_text(app, "PAUSED", paused_color, &app->pause_info.rect, 18);
}

void setup(App* app) {
    srand(time(NULL));

    app->current_algorithm = "Algorithm";

    if(!SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "%s\n", SDL_GetError());
    }

    if(!TTF_Init()) {
        fprintf(stderr, "Could not init TTF\n");
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

    app->pause_info.rect.x = 20;
    app->pause_info.rect.y = 20;

    load_media(app);
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

    SDL_RenderTexture(app->renderer, app->title.texture, NULL, &app->title.rect);

    SDL_SetRenderDrawColor(app->renderer, 0xa9, 0xb1, 0xd6, 255);
    SDL_RenderRect(app->renderer, &app->container);

    SDL_SetRenderDrawColor(app->renderer, 0x19, 0x19, 0x19, 255);
    SDL_RenderFillRect(app->renderer, &app->status_container);

    SDL_RenderTexture(app->renderer, app->info.texture, NULL, &app->info.rect);
    SDL_RenderTexture(app->renderer, app->pause_focus.texture, NULL, &app->pause_focus.rect);
    SDL_RenderTexture(app->renderer, app->second_pause_info.texture, NULL, &app->second_pause_info.rect);

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
