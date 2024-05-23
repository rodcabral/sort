#include <visualizer.h>
#include <sort.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    selection_sort(&app);

    for(int i = 0; i < LINES_SIZE; ++i) {
        app.lines[i].val = rand() % app.container.h;
    }

    bubble_sort(&app);

    clean_sdl(&app);

    return 0;
}
