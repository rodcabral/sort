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

    SDL_Color txt_color = {0xdd,0xdc,0xe8,255};
    // Title
    app->title_props.x = app->container.x;
    app->title_props.y = app->container.y - 40;
    
    app->title_texture = create_text(app, app->current_algorithm, txt_color, &app->title_props, 28);

    if(!app->title_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return;
    }

    // Array Access
    app->access_title_texture = create_text(app, "Array access:", txt_color, &app->access_title_props, 15);
    app->access_title_props.x = app->status_container.x + 10;
    app->access_title_props.y = app->status_container.y + 2;

    if(!app->access_title_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return;
    }
}

void setup(struct App* app) {
    app->is_running = init_window(app);
    
    app->current_algorithm = "Bubble Sort";

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
    
    shuffle_arr(app);

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
    load_media(app);
    SDL_SetRenderDrawColor(app->renderer, 0x14, 0x14, 0x13, 255);
    SDL_RenderClear(app->renderer);

    SDL_RenderCopyF(app->renderer, app->title_texture, NULL, &app->title_props);
    
    // Container
    SDL_SetRenderDrawColor(app->renderer, 0xdd, 0xdc, 0xe8, 255);
    SDL_RenderDrawRectF(app->renderer, &app->container);

    // Status Container
    SDL_SetRenderDrawColor(app->renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderFillRectF(app->renderer, &app->status_container);

    SDL_RenderCopyF(app->renderer, app->access_title_texture, NULL, &app->access_title_props);

    int gap = 1;
    
    int curr_x = app->container.x;
    for(int i = 0; i < LINES_SIZE; ++i) {
        app->lines[i].rect.y = app->container.y + app->container.h;
        app->lines[i].rect.w = (app->container.w / LINES_SIZE) - gap;
        app->lines[i].rect.x = curr_x;
        app->lines[i].rect.h = -(app->lines[i].val);
        
        curr_x += app->lines[i].rect.w + gap;

        if(app->is_sorted) {
            SDL_SetRenderDrawColor(app->renderer, 0x24, 0xff, 0x45, 255);
        } else {
            SDL_SetRenderDrawColor(app->renderer, 0xdd, 0xdc, 0xe8, 255);
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
    SDL_Delay(16);
}

void clean_sdl(struct App* app) {
    SDL_DestroyTexture(app->title_texture);

    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
}
