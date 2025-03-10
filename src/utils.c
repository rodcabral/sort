#include <utils.h>

bool is_array_sorted(struct App* app) {
    for(int i = 0; i < app->arr_size - 1; ++i) {
        if(app->lines[i].val > app->lines[i + 1].val) {
            return false;
        }
    }
    
    return true;
}

void shuffle_arr(struct App* app, int n) {
    app->arr_size = n;
    
    app->lines = malloc(sizeof(struct Line) * app->arr_size);

    int lim = app->container.h;
    for(int i = 0; i < app->arr_size; ++i) {
        app->lines[i].val = ((float)rand()/(float)(RAND_MAX)) * lim;
    }
}

SDL_Texture* create_text(struct App* app, const char* txt, SDL_Color color, SDL_FRect* props, int size) {
    TTF_Font* font = TTF_OpenFont("./fonts/Montserrat-Regular.otf", size);

    if(!font) {
        fprintf(stderr, "%s\n", TTF_GetError());
        return NULL;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(font, txt, color);

    if(!surface) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    props->w = surface->w;
    props->h = surface->h;
    
    SDL_Texture *new_texture = SDL_CreateTextureFromSurface(app->renderer, surface);

    if(!new_texture) {
        fprintf(stderr, "%s\n", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return new_texture;
}
