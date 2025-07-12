#ifndef _SORT_VISUALIZER_H_
#define _SORT_VISUALIZER_H_

#define WINDOW_WIDTH 900.0f
#define WINDOW_HEIGHT 650.0f

#define MAX_LENGTH 250

#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct {
    SDL_FRect rect;
    int value;
} Line;

typedef struct {
    bool is_running;

    int length;
    Line lines[MAX_LENGTH];

    SDL_Window* window;
    SDL_Renderer* renderer;
} App;

void setup(App *app);
void render(App* app);
void handle_input(App* app);

#endif

