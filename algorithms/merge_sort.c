#include "merge_sort.h"
#include "main.h"

static void merge(
    char* array_ptr,
    unsigned long array_half_len,
    unsigned long array_len,
    char (*condition_fn)(char, char))
{
    assert(array_ptr, "Null-pointer in merge");
    assert(condition_fn, "Null-pointer in merge");
    if(array_len > array_half_len){
        char* left_array = my_malloc((array_half_len)*sizeof(char));
        char* right_array = my_malloc((array_len-array_half_len)*sizeof(char));
        
        for(unsigned long i = 0; i < array_half_len; i++)
        {
            left_array[i] = array_ptr[i];
        }
        for(unsigned long i = 0; i < (array_len-array_half_len); i++)
        {
            right_array[i] = array_ptr[array_half_len + i];
        }
        
        unsigned long l = 0, r = 0;
        for(unsigned long i = 0; i < array_len; i++)
        {
            char comp_res = condition_fn(left_array[l],right_array[r]);
            if((0 == comp_res) &&
              (l < array_half_len))
            {
                array_ptr[i] = left_array[l];
                l++;
            }else 
            if((0 != comp_res) &&
               (r < (array_len-array_half_len)))
            {
                array_ptr[i] = right_array[r];
                r++;
            }
        }
        
        my_free(left_array);
        my_free(right_array);
    }
}

void merge_sort(
    char* array_ptr, 
    unsigned long array_len, 
    char (*condition_fn)(char, char)) 
{
    assert(array_ptr, "Null-pointer in merge_sort");
    assert(condition_fn, "Null-pointer in merge_sort");

    if (array_len >= 2){
        unsigned long array_half_len = array_len / 2;
        merge_sort(&array_ptr[0], array_half_len, condition_fn);
        merge_sort(&array_ptr[array_half_len], (array_len-array_half_len), condition_fn);
        merge(array_ptr, array_half_len, array_len, condition_fn);
    }
}
