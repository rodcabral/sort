#include "visualizer.h"
#include <sort.h>

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void bubble_sort(struct App* app) {
    for(int i = 0; i < LINES_SIZE; ++i) {
        for(int j = 0; j < LINES_SIZE - 1; ++j) {
            if(app->lines[j].val > app->lines[j + 1].val) {
                swap(&app->lines[j].val, &app->lines[j+1].val);
            }
            process_input(app);
            render(app, i, j);
            SDL_Delay(10);
        }
        if(!app->is_running) break;
    }
}
