#include <visualizer.h>
#include <sort.h>
#include <utils.h>

bool init_window(struct App* app) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return false;
    }

    if(TTF_Init() < 0) {
        fprintf(stderr, "%s\n", TTF_GetError());
        return false;
    }

    int init_wr = SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS, &app->window, &app->renderer);

    if(init_wr != 0) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return false;
    }

    return true;
}

void load_media(struct App* app) {
    SDL_Color txt_color = {0xc1, 0xc4, 0xdb, 255};

    // Title
    app->title_texture = create_text(app, app->current_algorithm, txt_color, &app->title_props, 20);
    app->title_props.x = app->container.x + (app->container.w/2) - app->title_props.w/2;
    app->title_props.y = app->container.y - 40;

    if(!app->title_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return;
    }

    // Status bar info
    char info_buffer[255];
    const char* c_info = info_buffer;

    snprintf(info_buffer, 255, "length:  %d  |  press", app->arr_size);
    app->info_texture = create_text(app, c_info, txt_color, &app->info_props, 13);
    app->info_props.x = app->status_container.x + 10;
    app->info_props.y = app->status_container.y + 1;

    if(!app->info_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return;
    }

    SDL_Color focus_color = {0xe0, 0xaf, 0x68, 255};

    app->pause_focus_texture = create_text(app, "  SPACE", focus_color, &app->pause_focus_props, 11);
    app->pause_focus_props.x = app->info_props.x + app->info_props.w;
    app->pause_focus_props.y = app->status_container.y + 3;

    if(!app->pause_focus_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return;
    }
    
    app->second_info_texture = create_text(app, "  to pause", txt_color, &app->second_info_props, 13);
    app->second_info_props.x = app->pause_focus_props.x + app->pause_focus_props.w;
    app->second_info_props.y = app->status_container.y + 1;

    if(!app->second_info_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return;
    }

    // Pause info
    SDL_Color paused_color = {0xff, 0x2e, 0x2e, 255};
    app->pause_info_texture = create_text(app, "PAUSED", paused_color, &app->pause_info_props, 18);
}

void setup(struct App* app) {
    app->is_running = init_window(app);
    
    app->current_algorithm = "x";

    // Container
    app->container.w = CONTAINER_WIDTH;
    app->container.h = CONTAINER_HEIGHT;
    app->container.x = (WINDOW_WIDTH / 2) - (CONTAINER_WIDTH / 2);
    app->container.y = (WINDOW_HEIGHT / 2) - (CONTAINER_HEIGHT / 2);

    // Status
    app->status_container.w = WINDOW_WIDTH;
    app->status_container.h = 20;
    app->status_container.x = 0;
    app->status_container.y = WINDOW_HEIGHT - app->status_container.h;

    // Paused
    app->pause_info_props.x = 20;
    app->pause_info_props.y = 20;

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
                    case SDLK_q:
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
    }
}

void render(struct App* app, int r) {
    SDL_SetRenderDrawColor(app->renderer, 0x1a, 0x1b, 0x26, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderCopyF(app->renderer, app->title_texture, NULL, &app->title_props);
    
    // Container
    SDL_SetRenderDrawColor(app->renderer, 0xa9, 0xb1, 0xd6, 255);
    SDL_RenderDrawRectF(app->renderer, &app->container);

    // Status Container
    SDL_SetRenderDrawColor(app->renderer, 0x32, 0x34, 0x4a, 255);
    SDL_RenderFillRectF(app->renderer, &app->status_container);

    SDL_RenderCopyF(app->renderer, app->info_texture, NULL, &app->info_props);
    SDL_RenderCopyF(app->renderer, app->pause_focus_texture, NULL, &app->pause_focus_props);
    SDL_RenderCopyF(app->renderer, app->second_info_texture, NULL, &app->second_info_props);

    int gap = 1;
    
    int curr_x = app->container.x;
    for(int i = 0; i < app->arr_size; ++i) {
        app->lines[i].rect.y = app->container.y + app->container.h;
        app->lines[i].rect.w = (app->container.w / app->arr_size) - gap;
        app->lines[i].rect.x = curr_x;
        app->lines[i].rect.h = -(app->lines[i].val);
        
        curr_x += app->lines[i].rect.w + gap;

        if(app->is_sorted) {
            SDL_SetRenderDrawColor(app->renderer, 0x24, 0xff, 0x45, 255);
        } else if(i == r + gap){
            SDL_SetRenderDrawColor(app->renderer, 0xff, 0x2e, 0x2e, 255);
        } else {
            SDL_SetRenderDrawColor(app->renderer, 0xac, 0xb0, 0xd0, 255);
        }

        SDL_RenderFillRectF(app->renderer, &app->lines[i].rect);
    }

    app->is_sorted = is_array_sorted(app);
    process_input(app);
    if(!app->is_running) {
        clean_sdl(app);
        exit(1);
    };

    SDL_RenderPresent(app->renderer);
}

void clean_sdl(struct App* app) {
    free(app->lines);

    SDL_DestroyTexture(app->title_texture);
    SDL_DestroyTexture(app->info_texture);
    SDL_DestroyTexture(app->pause_info_texture);
    SDL_DestroyTexture(app->pause_focus_texture);
    SDL_DestroyTexture(app->second_info_texture);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
