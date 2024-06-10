#ifndef _SORT_VISUALIZER_H_
#define _SORT_VISUALIZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 650

#define CONTAINER_WIDTH 800
#define CONTAINER_HEIGHT 450

struct Line {
    SDL_FRect rect;
    int val;
};

struct App {
    bool is_running;
    bool is_paused;
    bool is_sorted;

    SDL_Window* window;
    SDL_Renderer* renderer;

    // Container
    SDL_FRect container;

    // Current Algorithm Title
    SDL_Texture *title_texture;
    SDL_FRect title_props;
    const char* current_algorithm;

    int arr_size;
    struct Line * lines;

    // Status
    SDL_FRect status_container;

    SDL_Texture* info_texture;
    SDL_FRect info_props;

    // Pause info
    SDL_Texture* pause_info_texture;
    SDL_FRect pause_info_props;
    
    SDL_Texture* pause_focus_texture;
    SDL_FRect pause_focus_props;

    SDL_Texture* second_info_texture;
    SDL_FRect second_info_props;
};

bool init_window(struct App* app);

void load_media(struct App* app);

void setup(struct App* app);

void process_input(struct App* app);

void render(struct App* app, int r);

void clean_sdl(struct App* app);

#endif
