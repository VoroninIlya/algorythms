#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include "common_func.h"

// selection sort algorithm
void selection_sort(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

#endif // SELECTION_SORT_H
