#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "common_func.h"

// insertion sort algorithm
void insertion_sort(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

#endif // INSERTION_SORT_H
