#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "common_func.h"

#ifdef __cplusplus
extern "C" {
#endif

// merge sort algorithm
void merge_sort(
    char* array_ptr,                 // pointer to data array
    unsigned long array_len,         // data array length
    char (*condition_fn)(char, char) // condition function
);

#ifdef __cplusplus
}
#endif

#endif // MERGE_SORT_H
