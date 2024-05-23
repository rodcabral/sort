#include "visualizer.h"
#include <sort.h>

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void bubble_sort(struct App* app) {
    app->current_algorithm = "Bubble Sort";
    load_media(app);
    int b;
    for(int i = 0; i < LINES_SIZE; ++i) {
        for(int j = 0; j < LINES_SIZE - 1; ++j) {
            if(app->lines[j].val > app->lines[j + 1].val) {
                b = j;
                swap(&app->lines[j].val, &app->lines[j+1].val);
            }
        }
        process_input(app);
        render(app, i, b);
        SDL_Delay(42);
        if(!app->is_running) break;
    }
}

void selection_sort(struct App* app) {
    app->current_algorithm = "Selection Sort";
    load_media(app);
    int b;
    for(int i = 0; i < LINES_SIZE; ++i) {
        int min = i;
        int data_min = app->lines[i].val;
        for(int j = i; j < LINES_SIZE; ++j) {
            if(app->lines[j].val < data_min) {
                b = j;
                min = j;
                data_min = app->lines[j].val;
            }
        }
        int aux = app->lines[i].val;
        app->lines[i].val = data_min;
        app->lines[min].val = aux;
        process_input(app);
        render(app, i, b);
        SDL_Delay(42);
        if(!app->is_running) break;
    }
}
