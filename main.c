#include "./include/sort.h"

int main() {
    App app;

    setup(&app);

    bubble_sort(&app);
    selection_sort(&app);

    return 0;
}
