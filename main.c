#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    App app;
    setup(&app);
    
    app.current_algorithm = "Merge Sort";
    shuffle_arr(&app, 200);
    load_media(&app);
    merge_sort(&app, app.lines, 0, app.arr_size);
    if(app.is_sorted) {
        render(&app, 0);
        sleep(1);
    }

    shuffle_arr(&app, 100);
    bubble_sort(&app);

    shuffle_arr(&app, 200);
    selection_sort(&app);

    shuffle_arr(&app, 100);
    insertion_sort(&app);

    clean_sdl(&app);
    return 0;
}
