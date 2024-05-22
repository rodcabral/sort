#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

struct App {
    bool is_running;

    SDL_Window* window;
    SDL_Renderer* renderer;
};

bool init_window(struct App* app);

void process_input(struct App* app);

void clean_sdl(struct App* app);
