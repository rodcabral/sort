#include <visualizer.h>
#include <sort.h>

int main(void) {
    srand(time(NULL));
    printf("PID: %d\n", getpid());
    struct App app;
    
    setup(&app);

    bubble_sort(&app);

    clean_sdl(&app);

    return 0;
}
