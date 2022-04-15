#include "selection_sort.h"
#include "main.h"

void selection_sort(
    char* array_ptr, 
    unsigned long array_len, 
    char (*condition_fn)(char, char)) 
{
    assert(array_ptr, "Null-pointer in insertion_sort");
    assert(condition_fn, "Null-pointer in insertion_sort");
    for(unsigned long i = 0; i < array_len - 1; i++)
    {
        unsigned long min_index = i;
        for(unsigned long j = i + 1; j < array_len; j++)
        {
            if(condition_fn(array_ptr[min_index], array_ptr[j]))
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            char temp_byte = array_ptr[i];
            array_ptr[i] = array_ptr[min_index];
            array_ptr[min_index] = temp_byte;
        }
    }
}
