#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "common_func.h"

// quick sort algorithm
void quick_sort(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

// rendomized quick sort algorithm
void quick_sort_randomized(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

#endif // QUICK_SORT_H
