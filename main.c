#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    App app;
    setup(&app);
    
    bubble_sort(&app);
    selection_sort(&app);
    insertion_sort(&app);

    clean_sdl(&app);
    return 0;
}
