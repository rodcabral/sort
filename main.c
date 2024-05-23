#include <visualizer.h>
#include <sort.h>
#include <utils.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    selection_sort(&app);

    rand_array(&app);

    bubble_sort(&app);

    clean_sdl(&app);

    return 0;
}
