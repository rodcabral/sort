#ifndef _SORT_H_
#define _SORT_H_

#include <visualizer.h>

void bubble_sort(struct App* app);
void selection_sort(struct App* app);
void insertion_sort(struct App* app);

void merge(struct App* app, struct Line* lines, int l, int m, int r);
void merge_sort(struct App*, struct Line* lines, int l, int r);

#endif
