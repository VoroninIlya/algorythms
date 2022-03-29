#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "common_func.h"

// merge sort algorithm
void merge_sort(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

#endif // MERGE_SORT_H
