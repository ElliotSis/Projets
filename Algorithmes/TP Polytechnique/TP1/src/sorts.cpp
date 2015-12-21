#include "sorts.h"

#include <algorithm>
#include <iostream>

using namespace std;

// Swaping function
void swap(int* t, int i, int j){
	int tmp = t[i];
	t[i] = t[j];
	t[j] = tmp;
}

// Typedef of a bound generator for the generic bubble sort
typedef void(*bounds_generator)(int&, int&, int&);

// A partial generic bubble sort
void bubble_sort_partial(int* t, int start, int end, bounds_generator get_bounds) {
	bool is_sorted = false;
	int increment = 1;

	while(!is_sorted) {
		is_sorted = true;

		for(int i = start; i != end; i += increment) {
			if((increment < 0) ? (t[i+increment] > t[i]) : (t[i] > t[i+increment])) {
				swap(t, i, i+increment);
				is_sorted = false;
			}
		}

		(*get_bounds)(start, end, increment);
	}
}

// A full, generic, bubble sort
void bubble_sort_generic(int* t, int n, bounds_generator get_bounds){
	bubble_sort_partial(t, 0, n-1, get_bounds);
}

// The different bounds generator that will be used
void bubble_bounds(int& start, int& end, int& increment) {}

void shaker_bounds(int& start, int& end, int& increment) {
	int tmp = start;
	start = end - increment;
	end = tmp;
	increment = -increment;
}

// The bubble sorts
void bubble_sort(int* t, int n) {
	bubble_sort_generic(t, n, bubble_bounds);
}

void shaker_sort(int* t, int n) {
	bubble_sort_generic(t, n, shaker_bounds);
}

// Typedef for the pivot function
typedef int(*pivot_generator)(int, int);

// Generic partition function of the quick sort
int partition(int* t, int start, int end, pivot_generator get_pivot) {
	int pivot_position = get_pivot(start, end);
	int pivot = t[pivot_position];

	while(start <= end) {
		if(t[start] <= pivot) {
			start++;
		}
		else if (t[end] > pivot) {
			end--;
		}
		else {
			swap(t, start, end);
		}
	}

	swap(t, pivot_position, end);

	return end;
}

// Generic and partial quick sort
void quick_sort_partial(int* t, int start, int end, int recursive_limit, pivot_generator get_pivot) {
	if(end-start > recursive_limit) {
		int pivot_position = partition(t, start, end, get_pivot);
		quick_sort_partial(t, start, pivot_position-1, recursive_limit, get_pivot);
		quick_sort_partial(t, pivot_position+1, end, recursive_limit, get_pivot);
	}
	else if (start < end) {
		bubble_sort_partial(t, start, end, shaker_bounds);
	}
}

// Generic, full, quick sort
void quick_sort_generic(int* t, int n, int recursive_limit, pivot_generator get_pivot){
	quick_sort_partial(t, 0, n-1, recursive_limit, get_pivot);
}

// The different functions to compute the pivot
int basic_pivot(int start, int end) {
	return (start);
}

int random_pivot(int start, int end) {
	return (start + int((end-start+1)*rand()/(RAND_MAX + 1.0)));
}

// The optimal recursive limit
const int RECURSIVE_LIMIT = 8;

// The different quick sorts
void quick_sort(int* t, int n) {
	quick_sort_generic(t, n, 0, basic_pivot);
}

void quick_sort_random_pivot(int* t, int n) {
	quick_sort_generic(t, n, 0, random_pivot);
}

void quick_sort_recursive_stop(int* t, int n) {
	quick_sort_generic(t, n, RECURSIVE_LIMIT, basic_pivot);
}

void quick_sort_random_pivot_recursive_stop(int* t, int n){
	quick_sort_generic(t, n, RECURSIVE_LIMIT, random_pivot);
}

void quick_sort_recursive_stop_limit(int* t, int n, int l){
	quick_sort_generic(t, n, l, basic_pivot);
}

void quick_sort_random_pivot_recursive_stop_limit(int* t, int n, int l){
	quick_sort_generic(t, n, l, random_pivot);
}

// The std sort
void std_sort(int* t, int n) {
	sort(t, t+n);
}
