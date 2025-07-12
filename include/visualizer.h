#ifndef _SORT_VISUALIZER_H_
#define _SORT_VISUALIZER_H_

#define WINDOW_WIDTH 900.0f
#define WINDOW_HEIGHT 650.0f
#define CONTAINER_WIDTH 800.0f
#define CONTAINER_HEIGHT 400.0f

#define MAX_LENGTH 250

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct {
    SDL_FRect rect;
    int value;
} Line;

typedef struct {
    bool is_running;
    bool is_sorted;

    int length;
    Line lines[MAX_LENGTH];

    SDL_FRect container;
    SDL_FRect status_container;

    SDL_Window* window;
    SDL_Renderer* renderer;
} App;

void setup(App *app);
void render(App* app, int r);
void handle_input(App* app);

#endif

