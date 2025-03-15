#ifndef _SORT_H_
#define _SORT_H_

#include <visualizer.h>

void bubble_sort(App* app);
void selection_sort(App* app);
void insertion_sort(App* app);

void merge(App* app, Line* lines, int l, int m, int r);
void merge_sort(App*, Line* lines, int l, int r);

#endif
