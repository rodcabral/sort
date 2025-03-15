#include "./include/visualizer.h"
#include "./include/sort.h"

int main(void) {
    App app;
    setup(&app);
    
    merge_sort(&app);
    bubble_sort(&app);
    selection_sort(&app);
    insertion_sort(&app);

    clean_sdl(&app);
    return 0;
}
