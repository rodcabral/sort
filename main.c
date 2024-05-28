#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    bubble_sort(&app);

    rand_array(&app);

    insertion_sort(&app);
    
    rand_array(&app);

    selection_sort(&app);

    rand_array(&app);

    clean_sdl(&app);

    return 0;
}
