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
#define CONTAINER_HEIGHT 400
#define MAX_LENGTH 200

typedef struct {
    SDL_FRect rect;
    int val;
} Line;

typedef struct {
    bool is_running;
    bool is_paused;
    bool is_sorted;

    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_FRect container;

    SDL_Texture *title_texture;
    SDL_FRect title_props;
    const char* current_algorithm;

    int arr_size;
    Line lines[MAX_LENGTH];

    SDL_FRect status_container;

    SDL_Texture* info_texture;
    SDL_FRect info_props;

    SDL_Texture* pause_info_texture;
    SDL_FRect pause_info_props;
    
    SDL_Texture* pause_focus_texture;
    SDL_FRect pause_focus_props;

    SDL_Texture* second_info_texture;
    SDL_FRect second_info_props;
} App;

void load_media(App* app);

void setup(App* app);

void process_input(App* app);

void render(App* app, int r);

void clean_sdl(App* app);

#endif
