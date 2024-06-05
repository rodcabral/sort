#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    // Merge Sort
    shuffle_arr(&app, 200);
    merge_sort(&app, app.lines, 0, app.arr_size);
    if(app.is_sorted) {
        render(&app, 0);
        sleep(1);
    }

    // Selection Sort
    shuffle_arr(&app, 200);
    selection_sort(&app);

    // Bubble Sort
    shuffle_arr(&app, 100);
    bubble_sort(&app);

    // Insertion sort
    shuffle_arr(&app, 100);
    insertion_sort(&app);

    clean_sdl(&app);
    return 0;
}
