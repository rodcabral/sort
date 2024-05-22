#include <visualizer.h>

int main(void) {
    printf("PID: %d\n", getpid());

    struct App app;
    
    app.is_running = init_window(&app);

    while(app.is_running) {
        render(&app);
        process_input(&app);
    }

    clean_sdl(&app);

    return 0;
}
