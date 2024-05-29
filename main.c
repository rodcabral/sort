#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    merge_sort(&app, app.lines, 0, LINES_SIZE);

    rand_array(&app);

    bubble_sort(&app);

    rand_array(&app);

    insertion_sort(&app);
    
    rand_array(&app);

    selection_sort(&app);

    rand_array(&app);

    clean_sdl(&app);

    return 0;
}
