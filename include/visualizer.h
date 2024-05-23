#ifndef _SORT_VISUALIZER_H_
#define _SORT_VISUALIZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#define CONTAINER_WIDTH 1200
#define CONTAINER_HEIGHT 650

#define LINES_SIZE 300

struct Line {
    SDL_Rect rect;
    int val;
};

struct App {
    bool is_running;

    SDL_Window* window;
    SDL_Renderer* renderer;

    // Container
    SDL_Rect container;

    // Current Algorithm Title
    SDL_Texture *title_texture;
    SDL_Rect title_props;
    const char* current_algorithm;

    struct Line lines[LINES_SIZE];
};

bool init_window(struct App* app);

void load_media(struct App* app);

void setup(struct App* app);

void process_input(struct App* app);

void render(struct App* app, int i, int j);

void clean_sdl(struct App* app);

#endif
