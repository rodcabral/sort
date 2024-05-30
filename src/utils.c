#include <utils.h>

bool is_array_sorted(struct App* app) {
    for(int i = 0; i < LINES_SIZE - 1; ++i) {
        if(app->lines[i].val > app->lines[i + 1].val) {
            return false;
        }
    }
    
    return true;
}

void shuffle_arr(struct App* app) {
    int lim = app->container.h;
    for(int i = 0; i < LINES_SIZE; ++i) {
        app->lines[i].val = ((float)rand()/(float)(RAND_MAX)) * lim;
    }
}
