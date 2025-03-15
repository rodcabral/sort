#include <visualizer.h>
#include <sort.h>

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void bubble_sort(App* app) {
    shuffle_arr(app, 100);
    app->current_algorithm = "Bubble Sort";
    load_media(app);
    for(int i = 0; i < app->arr_size; ++i) {
        for(int j = 0; j < app->arr_size - i - 1; ++j) {
            if(app->lines[j].val > app->lines[j + 1].val) {
                swap(&app->lines[j].val, &app->lines[j+1].val);
                render(app, j);
                
                while(app->is_paused) {
                    process_input(app);
                    if(!app->is_running) {
                        clean_sdl(app);
                        exit(1);
                    }
                    SDL_RenderCopyF(app->renderer, app->pause_info_texture, NULL, &app->pause_info_props);
                    SDL_RenderPresent(app->renderer);
                }

                SDL_Delay(12);
            }
        }
    }

    app->is_sorted = true;
    render(app, 0);
    sleep(1);
}

void selection_sort(App* app) {
    shuffle_arr(app, 200);
    app->current_algorithm = "Selection Sort";
    load_media(app);
    for(int i = 0; i < app->arr_size; ++i) {
        int min = i;
        int data_min = app->lines[i].val;
        for(int j = i; j < app->arr_size; ++j) {
            if(app->lines[j].val < data_min) {
                min = j;
                data_min = app->lines[j].val;
                render(app, j);
                
                while(app->is_paused) {
                    process_input(app);
                    if(!app->is_running) {
                        clean_sdl(app);
                        exit(1);
                    }
                    SDL_RenderCopyF(app->renderer, app->pause_info_texture, NULL, &app->pause_info_props);
                    SDL_RenderPresent(app->renderer);
                }

                SDL_Delay(12);
            }
        }
        swap(&app->lines[i].val, &app->lines[min].val);
    }

    app->is_sorted = true;
    render(app, 0);
    sleep(1);
}

void insertion_sort(App* app) {
    shuffle_arr(app, 100);
    app->current_algorithm = "Insertion Sort";
    load_media(app);

    for(int i = 0; i < app->arr_size; ++i) {
        int j = i;

        while(j > 0 && app->lines[j].val < app->lines[j-1].val) {
            swap(&app->lines[j].val, &app->lines[j-1].val);
            j--;

            process_input(app);
            if(!app->is_running) break;
            render(app, i-1);

            while(app->is_paused) {
                process_input(app);
                if(!app->is_running) {
                    clean_sdl(app);
                    exit(1);
                }
                SDL_RenderCopyF(app->renderer, app->pause_info_texture, NULL, &app->pause_info_props);
                SDL_RenderPresent(app->renderer);
            } 

            SDL_Delay(12);
        } 
    }

    app->is_sorted = true;
    render(app, 0);
    sleep(1);
}
