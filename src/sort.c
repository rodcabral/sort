#include "../include/sort.h"

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void sorted(App* app) {
    app->is_sorted = true;
    render(app, 0);
    sleep(1);
    app->is_sorted = false;
}

void shuffle(App* app, int n) {
    app->length = n;
    
    for(int i = 0; i < app->length; ++i) {
        app->lines[i].value = (int)rand() % (int)app->container.h;
    }
}

void bubble_sort(App* app) {
    shuffle(app, 100);
    for(int i = 0; i < app->length; ++i) {
        for(int j = 0; j < app->length - i - 1; ++j) {
            if(app->lines[j].value > app->lines[j + 1].value) {
                swap(&app->lines[j].value, &app->lines[j+1].value);
                render(app, j);
                
                SDL_Delay(10);
            }
        }
    }

    sorted(app);
}
