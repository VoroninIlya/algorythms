#include "insertion_sort.h"
#include "main.h"

void insertion_sort(
    char* array_ptr, 
    unsigned long array_len,
    char (*condition_fn)(char, char))
{
    assert(condition_fn, "Null-pointer in insertion_sort");
    for(unsigned long j = 1; j < array_len; j++)
    {
        long i = j - 1;
        char temp_byte = array_ptr[j];

        while((i >= 0) && 
              (condition_fn(array_ptr[i],temp_byte)))
        {
            array_ptr[i + 1] = array_ptr[i];
            i -= 1;
        }
        array_ptr[i + 1] = temp_byte;
    }
}
