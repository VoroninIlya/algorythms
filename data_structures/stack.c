#include "stack.h"
#include "main.h"

char stack_init(stack_t* const stack_ptr, unsigned long int size)
{
    if ((NULL == stack_ptr->main_ptr) &&
        (NULL == stack_ptr->top_ptr))
    {
        stack_ptr->main_ptr = my_malloc(size);
        if (NULL != stack_ptr->main_ptr)
        {
            stack_ptr->top_ptr = stack_ptr->main_ptr;
            stack_ptr->size = size;
        }
    }
    return 1;
}

char is_stack_empty(stack_t* const stack_ptr)
{
    char result = 0;
    if ((NULL != stack_ptr->main_ptr) && 
        (stack_ptr->main_ptr == stack_ptr->top_ptr))
    {
        result = 1;
    }
    
    return result;
}

unsigned long int get_stack_number_of_elements(stack_t* const stack_ptr)
{
    return (unsigned long int)(stack_ptr->top_ptr - stack_ptr->main_ptr);
}

unsigned long int get_stack_free_space(stack_t* const stack_ptr)
{
    return stack_ptr->size - get_stack_number_of_elements(stack_ptr);
}

char push_byte(stack_t* const stack_ptr, char byte)
{
    char result = 0;
    if (0 < get_stack_free_space(stack_ptr))
    {
        *(stack_ptr->top_ptr++) = byte;
        result = 1;
    }
    return result;
}

char pop_byte(stack_t* const stack_ptr, char* byte)
{
    char result = 0;
    if (1 != is_stack_empty(stack_ptr))
    {
        *byte =  *(--stack_ptr->top_ptr);
        result = 1;
    }
    return result;
}

char push_byte_array(stack_t* const stack_ptr, char* array, unsigned long int data_len)
{
    char result = 0;
    if (data_len <= get_stack_free_space(stack_ptr))
    {
        for(unsigned long int i = 0; i < data_len; i++)
        {
            *(stack_ptr->top_ptr++) = array[i];
        }
        result = 1;
    }
    return result;
}

char pop_byte_array(stack_t* const stack_ptr, char* array, unsigned long int data_len)
{
    char result = 0;
    if (data_len <= get_stack_number_of_elements(stack_ptr))
    {
        for(unsigned long int i = 0; i < data_len; i++)
        {
            array[i] = *(--stack_ptr->top_ptr);
        }
        result = 1;
    }
    return result;
}

void print_stack_content(stack_t* const stack_ptr)
{
    unsigned long int numb_of_elements = get_stack_number_of_elements(stack_ptr);
    
    for(unsigned long int i = 0; i < numb_of_elements; i++)
    {
        printf("%02X ", stack_ptr->main_ptr[i]);
    }
    printf("\n");
}
