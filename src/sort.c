#include "visualizer.h"
#include <sort.h>
#include <unistd.h>

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}

void bubble_sort(struct App* app) {
    app->current_algorithm = "Bubble Sort";
    for(int i = 0; i < LINES_SIZE; ++i) {
        for(int j = 0; j < LINES_SIZE - 1; ++j) {
            if(app->lines[j].val > app->lines[j + 1].val) {
                swap(&app->lines[j].val, &app->lines[j+1].val);
            }
        }
        render(app);
        SDL_Delay(42);
    }

    if(app->is_sorted) {
        render(app);
        sleep(1);
    }
}

void selection_sort(struct App* app) {
    app->current_algorithm = "Selection Sort";
    for(int i = 0; i < LINES_SIZE; ++i) {
        int min = i;
        int data_min = app->lines[i].val;
        for(int j = i; j < LINES_SIZE; ++j) {
            if(app->lines[j].val < data_min) {
                min = j;
                data_min = app->lines[j].val;
            }
        }
        swap(&app->lines[i].val, &app->lines[min].val);
        render(app);
        SDL_Delay(42);
    }

    if(app->is_sorted) {
        render(app);
        sleep(1);
    }
}

void insertion_sort(struct App* app) {
    app->current_algorithm = "Insertion Sort";

    for(int i = 0; i < LINES_SIZE; ++i) {
        int j = i;

        while(j > 0 && app->lines[j].val < app->lines[j-1].val) {
            swap(&app->lines[j].val, &app->lines[j-1].val);
            j--;

            process_input(app);
            if(!app->is_running) break;
        } 
        render(app);
        SDL_Delay(42);
    }

    if(app->is_sorted) {
        render(app);
        sleep(1);
    }
}

void merge(struct App* app, struct Line* lines, int l, int m, int r) {
    app->current_algorithm = "Merge Sort";

    int n1 = m - l + 1;
    int n2 = r - m;
    
    struct Line L[n1];
    struct Line R[n2];

    for(int i = 0; i < n1; ++i) {
        L[i].val = lines[l + i].val;
    }

    for(int j = 0; j < n2; ++j) {
        R[j].val = lines[m + 1 + j].val;
    }

    int i = 0;
    int j = 0;
    int k = l;

    while(i < n1 && j < n2) {
        if(L[i].val <= R[j].val) {
            lines[k].val = L[i].val;
            i++;
        } else {
            lines[k] = R[j];
            j++;
        }
        k++;
        render(app);
    }

    while(i < n1) {
        lines[k].val = L[i].val;
        i++;
        k++;
    }

    while(j < n2) {
        lines[k].val = R[j].val;
        j++;
        k++;
    } 
}

void merge_sort(struct App* app, struct Line* lines, int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
        
        merge_sort(app, lines, l, m);
        merge_sort(app, lines, m+1, r);
        merge(app, lines, l, m, r);
        if(app->is_sorted) {
            render(app);
            sleep(1);
            return;
        }
    }

    if(app->is_sorted) {
        render(app);
        sleep(1);
        return;
    }
}
