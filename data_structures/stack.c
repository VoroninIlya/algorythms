#include "stack.h"

void stack_set_alloc_cb(stack_t* const stack_ptr, stack_allocCb_t alcb) {
    stack_ptr->allocCb = alcb;
}

void stack_set_free_cb(stack_t* const stack_ptr, stack_freeCb_t free) {
    stack_ptr->freeCb = free;
}

void stack_init(stack_t* const stack_ptr, unsigned long int size)
{
    if ((NULL == stack_ptr->main_ptr) &&
        (NULL == stack_ptr->top_ptr) && 
        (NULL != stack_ptr->allocCb) && 
        (NULL != stack_ptr->freeCb))
    {
        stack_ptr->main_ptr = (char*)stack_ptr->allocCb(size);
        if (NULL != stack_ptr->main_ptr)
        {
            stack_ptr->top_ptr = stack_ptr->main_ptr;
            stack_ptr->size = size;
        }
    }
}

void stack_deinit(stack_t* const stack_ptr)
{
    if (NULL != stack_ptr->main_ptr)
    {
        if(NULL != stack_ptr->freeCb) {
            stack_ptr->freeCb(stack_ptr->main_ptr);
        }
        stack_ptr->main_ptr = NULL;
        stack_ptr->top_ptr = NULL;
        stack_ptr->size = 0;
    }
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
    unsigned long int top_ptr_index = stack_ptr->top_ptr - stack_ptr->main_ptr;
    
    
    for(unsigned long int i = 0; i <= stack_ptr->size; i++)
    {
        if (i == top_ptr_index)
        {
            printf(" T ");
        }else
        {
            printf("   ");
        }
    }
    printf("\n");
    for(unsigned long int i = 0; i < stack_ptr->size; i++)
    {
        if (i < top_ptr_index)
        {
            printf("|%02X", stack_ptr->main_ptr[i]);
        }else
        {
            printf("|  ");
        }
    }
    printf("|\n");
}
