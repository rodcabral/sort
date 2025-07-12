#include "../include/sort.h"

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void shuffle(App* app, int n) {
    app->length = n;
    
    for(int i = 0; i < app->length; ++i) {
        app->lines[i].value = (int)rand() % (int)app->container.h;
    }
}
