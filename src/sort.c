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
        SDL_RenderTexture(app->renderer, app->pause_info.texture, NULL, &app->pause_info.rect);
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
    app->current_algorithm = "Bubble Sort";
    load_media(app);
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

    app->current_algorithm = "Selection Sort";
    load_media(app);

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

    app->current_algorithm = "Insertion Sort";
    load_media(app);

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


void merge(App* app, Line* lines, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Line L[n1];
    Line R[n2];

    for(int i = 0; i < n1; ++i) {
        L[i].value = lines[l + i].value;
    }

    for(int j = 0; j < n2; ++j) {
        R[j].value = lines[m + 1 + j].value;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while(i < n1 && j < n2) {
        if(L[i].value <= R[j].value) {
            lines[k].value = L[i].value;
            i++;
        } else {
            lines[k] = R[j];
            j++;
        }
        k++;
        render(app, k);

        pause_sort(app);

        SDL_Delay(10);
    }

    while(i < n1) {
        lines[k].value = L[i].value;
        i++;
        k++;
    }

    while(j < n2) {
        lines[k].value = R[j].value;
        j++;
        k++;
    } 
}

void _merge_sort(App* app, Line* lines, int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
 
        if(l >= app->length/2 && l <= (app->length/2) + 1) {
            SDL_DestroyTexture(app->title.texture);
            SDL_DestroyTexture(app->info.texture);

            app->current_algorithm = "Merge Sort";
            load_media(app);
        }
        
        _merge_sort(app, lines, l, m);
        _merge_sort(app, lines, m+1, r);
        merge(app, lines, l, m, r);
    }
}

void merge_sort(App* app) {
    app->current_algorithm = "Merge Sort";
    shuffle(app, 200);
    load_media(app);
    _merge_sort(app, app->lines, 0, app->length);

    sorted(app);
}
