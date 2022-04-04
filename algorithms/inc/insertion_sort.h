#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "common_func.h"

#ifdef __cplusplus
extern "C" {
#endif

// insertion sort algorithm
void insertion_sort(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

#ifdef __cplusplus
}
#endif

#endif // INSERTION_SORT_H
