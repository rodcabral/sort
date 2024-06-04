#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    // Bubble Sort
    bubble_sort(&app);

    // Merge Sort
    shuffle_arr(&app);
    merge_sort(&app, app.lines, 0, LINES_SIZE);
    // Insertion sort
    shuffle_arr(&app);
    insertion_sort(&app);

    // Selection Sort
    shuffle_arr(&app);
    selection_sort(&app);

    clean_sdl(&app);
    return 0;
}
