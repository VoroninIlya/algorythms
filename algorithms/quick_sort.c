#include "quick_sort.h"
#include "main.h"


static unsigned long partition(
    char* array_ptr,
    unsigned long array_len,
    const char (*condition_fn)(char, char))
{
    long j = -1;
    
    assert(array_ptr, "Null-pointer in partition");
    assert(condition_fn, "Null-pointer in partition");
    
    if (2 <= array_len)
    {
        char* pivot_ptr = &array_ptr[array_len-1];
        for(unsigned long i = 0; i < array_len-1; i++)
        {
            if (condition_fn(array_ptr[i], *pivot_ptr))
            {
                j++;
                char tmp = array_ptr[j];
                array_ptr[j] = array_ptr[i];
                array_ptr[i] = tmp;
            }
        }
        char tmp = *pivot_ptr;
        *pivot_ptr = array_ptr[j+1];
        array_ptr[j+1] = tmp;
    }
    return (j+1);
}

void quick_sort(
    char* array_ptr, 
    unsigned long array_len, 
    const char (*condition_fn)(char, char)) 
{
    unsigned long curr_index = 0;
    
    assert(array_ptr, "Null-pointer in quick_sort");
    assert(condition_fn, "Null-pointer in quick_sort");
    
    if(0 < array_len)
    {
        curr_index = partition(array_ptr, array_len, condition_fn);
        quick_sort(&array_ptr[0], curr_index, condition_fn);
        quick_sort(&array_ptr[curr_index+1], (array_len-curr_index-1), condition_fn);
    }
}

static unsigned long get_random(unsigned long max_val)
{
    unsigned long
    // max_val <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max_val + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;
  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);
  // Truncated division is intentional
  return x/bin_size;
}

static unsigned long partition_randomized(
    char* array_ptr,
    unsigned long array_len,
    const char (*condition_fn)(char, char))
{
    unsigned long pivot_index = get_random(array_len-1);
    char tmp = array_ptr[array_len-1];
    array_ptr[array_len-1] = array_ptr[pivot_index];
    array_ptr[pivot_index] = tmp;
    
    return partition(array_ptr, array_len, condition_fn);
}

void quick_sort_randomized(
    char* array_ptr, 
    unsigned long array_len, 
    const char (*condition_fn)(char, char)) 
{
    unsigned long curr_index = 0;
    
    assert(array_ptr, "Null-pointer in quick_sort");
    assert(condition_fn, "Null-pointer in quick_sort");
    
    if(0 < array_len)
    {
        curr_index = partition_randomized(array_ptr, array_len, condition_fn);
        quick_sort_randomized(&array_ptr[0], curr_index, condition_fn);
        quick_sort_randomized(&array_ptr[curr_index+1], (array_len-curr_index-1), condition_fn);
    }
}