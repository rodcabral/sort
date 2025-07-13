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

void pause_sort(App* app) {
    while(app->is_paused) {
        handle_input(app);
        if(!app->is_running) {
            clean_sdl(app);
            exit(1);
        }
        SDL_RenderPresent(app->renderer);
    }
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

                pause_sort(app);
                
                SDL_Delay(10);
            }
        }
    }

    sorted(app);
}

void selection_sort(App* app) {
    shuffle(app, 200);
    for(int i = 0; i < app->length; ++i) {
        int min = i;
        int data_min = app->lines[i].value;
        for(int j = i; j < app->length; ++j) {
            if(app->lines[j].value < data_min) {
                min = j;
                data_min = app->lines[j].value;
                render(app, j - 1);

                pause_sort(app);
                
                SDL_Delay(10);
            }
        }
        swap(&app->lines[i].value, &app->lines[min].value);
    }

    sorted(app);
}

void insertion_sort(App* app) {
    shuffle(app, 100);

    for(int i = 0; i < app->length; ++i) {
        int j = i;

        while(j > 0 && app->lines[j].value < app->lines[j-1].value) {
            swap(&app->lines[j].value, &app->lines[j-1].value);
            j--;

            handle_input(app);
            if(!app->is_running) break;
            render(app, j-1);

            pause_sort(app);            

            SDL_Delay(10);
        } 
    }

    sorted(app);
}
