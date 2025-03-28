#ifndef _SORT_VISUALIZER_H_
#define _SORT_VISUALIZER_H_

#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 900.0f
#define WINDOW_HEIGHT 650.0f
#define CONTAINER_WIDTH 800.0f
#define CONTAINER_HEIGHT 400.0f

#define MAX_LENGTH 250

typedef struct {
    SDL_FRect rect;
    int value;
} Line;

typedef struct {
    SDL_FRect rect;
    SDL_Texture *texture;
} Object;

typedef struct {
    bool is_running;
    bool is_paused;
    bool is_sorted;

    int length;
    Line lines[MAX_LENGTH];

    SDL_Window* window;
    SDL_Renderer* renderer;

    const char* current_algorithm;
    SDL_FRect container;
    SDL_FRect status_container;

    Object title;
    Object info;
    Object pause_info;
    Object pause_focus;
    Object second_pause_info;
} App;

void load_media(App* app);

void setup(App* app);

void handle_input(App* app);

void render(App* app, int r);

void clean_sdl(App* app);

SDL_Texture* create_text(App* app, const char* txt, SDL_Color color, SDL_FRect* props, int size);

#endif
