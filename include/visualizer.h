#ifndef _SORT_VISUALIZER_H_
#define _SORT_VISUALIZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 850
#define WINDOW_HEIGHT 600

#define CONTAINER_WIDTH 750
#define CONTAINER_HEIGHT 400

#define LINES_SIZE 150

struct Line {
    SDL_FRect rect;
    int val;
};

struct App {
    bool is_running;

    SDL_Window* window;
    SDL_Renderer* renderer;

    // Container
    SDL_FRect container;

    // Current Algorithm Title
    SDL_Texture *title_texture;
    SDL_FRect title_props;
    const char* current_algorithm;

    struct Line lines[LINES_SIZE];

    // Status
    SDL_FRect status_container;

    SDL_Texture* access_texture;
    SDL_FRect access_props;
    int access;

    bool is_sorted;
};

bool init_window(struct App* app);

void load_media(struct App* app);

void setup(struct App* app);

void process_input(struct App* app);

void render(struct App* app);

void clean_sdl(struct App* app);

#endif
