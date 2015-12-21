#ifndef SORTS_H
#define SORTS_H

#include <string>

// Typedef of a sorting function
typedef void(*sort_function)(int*, int);

// The sorts
void bubble_sort(int* t, int n);
void shaker_sort(int* t, int n);
void quick_sort(int* t, int n);
void quick_sort_random_pivot(int* t, int n);
void quick_sort_recursive_stop(int* t, int n);
void quick_sort_random_pivot_recursive_stop(int* t, int n);
void std_sort(int* t, int n);

void quick_sort_recursive_stop_limit(int* t, int n, int l);
void quick_sort_random_pivot_recursive_stop_limit(int* t, int n, int l);

const int NUMBER_OF_SORTS = 7;
const sort_function sort_functions[NUMBER_OF_SORTS] = {bubble_sort, shaker_sort, quick_sort, quick_sort_random_pivot, quick_sort_recursive_stop, quick_sort_random_pivot_recursive_stop, std_sort};
const std::string sort_functions_names[NUMBER_OF_SORTS] = {"bubble_sort", "shaker_sort", "quick_sort", "quick_sort_random_pivot", "quick_sort_recursive_stop", "quick_sort_random_pivot_recursive_stop", "std_sort"};

#endif // SORTS_H