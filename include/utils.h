#ifndef _VISUALIZER_UTILS_H_
#define _VISUALIZER_UTILS_H_

#include <visualizer.h>
#include <stdbool.h>

bool is_array_sorted(App* app);

void shuffle_arr(App* app, int n);

SDL_Texture* create_text(App* app, const char* txt, SDL_Color color, SDL_FRect* props, int size);

#endif
