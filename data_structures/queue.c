#include "queue.h"
#include "main.h"

void queue_init(queue_t* const queue_ptr, unsigned long int size)
{
    if ((NULL == queue_ptr->main_ptr) &&
        (NULL == queue_ptr->head_ptr) &&
        (NULL == queue_ptr->tail_ptr))
    {
        queue_ptr->main_ptr = my_malloc(size);
        if (NULL != queue_ptr->main_ptr)
        {
            queue_ptr->tail_ptr = queue_ptr->head_ptr = queue_ptr->main_ptr;
            queue_ptr->size = size;
        }
    }
}

void queue_deinit(queue_t* const queue_ptr)
{
    if (NULL != queue_ptr->main_ptr)
    {
        my_free(queue_ptr->main_ptr);
        queue_ptr->main_ptr = NULL;
        queue_ptr->head_ptr = NULL;
        queue_ptr->tail_ptr = NULL;
        queue_ptr->size = 0;
    }
}

char is_queue_empty(queue_t* const queue_ptr)
{
    char result = 0;
    if ((NULL != queue_ptr->head_ptr) && 
        (queue_ptr->head_ptr == queue_ptr->tail_ptr))
    {
        result = 1;
    }
    return result;
}

unsigned long int get_queue_number_of_elements(queue_t* const queue_ptr)
{
    unsigned long int result = 0;
    if (queue_ptr->head_ptr <= queue_ptr->tail_ptr)
    {
        result = (unsigned long int)(queue_ptr->tail_ptr - queue_ptr->head_ptr);
    }else
    {
        result = (unsigned long int)(queue_ptr->tail_ptr + 1 - queue_ptr->main_ptr) +
            queue_ptr->size - (unsigned long int)(queue_ptr->head_ptr - queue_ptr->main_ptr);
    }
    return result;
}

unsigned long int get_queue_free_space(queue_t* const queue_ptr)
{
    return queue_ptr->size - get_queue_number_of_elements(queue_ptr);
}

char enqueue_byte(queue_t* const queue_ptr, char byte)
{
    char result = 0;
    if (0 < get_queue_free_space(queue_ptr))
    {
        if (queue_ptr->tail_ptr >= queue_ptr->head_ptr)
        {
            if (queue_ptr->tail_ptr >= 
            (queue_ptr->main_ptr + queue_ptr->size))
            {
                queue_ptr->tail_ptr = queue_ptr->main_ptr;
                *(queue_ptr->tail_ptr) = byte;
            }else
            {
                *(queue_ptr->tail_ptr) = byte;
                queue_ptr->tail_ptr++;
            }
            
        }else
        {
            queue_ptr->tail_ptr++;
            *(queue_ptr->tail_ptr) = byte;
        }
        
        result = 1;
    }
    return result;
}

char dequeue_byte(queue_t* const queue_ptr, char* byte)
{
    char result = 0;
    if (1 != is_queue_empty(queue_ptr))
    {
        if (queue_ptr->head_ptr >= queue_ptr->main_ptr + queue_ptr->size)
        {
            queue_ptr->head_ptr = queue_ptr->main_ptr;
            *byte =  *(queue_ptr->head_ptr);
            *(queue_ptr->head_ptr) = 0x0;
        }else
        {
            *byte =  *(queue_ptr->head_ptr);
            *(queue_ptr->head_ptr) = 0x0;
            queue_ptr->head_ptr++;
            if (queue_ptr->head_ptr >= queue_ptr->main_ptr + queue_ptr->size)
            {
                if (1 != is_queue_empty(queue_ptr))
                {
                    queue_ptr->head_ptr = queue_ptr->main_ptr;
                    if (queue_ptr->tail_ptr == queue_ptr->head_ptr){
                        queue_ptr->tail_ptr++;
                    }
                }else
                {
                    queue_ptr->head_ptr = queue_ptr->main_ptr;
                    queue_ptr->tail_ptr = queue_ptr->main_ptr;
                }
            }
        }
        result = 1;
    }
    return result;
}

char enqueue_byte_array(queue_t* const queue_ptr, char* array, unsigned long int data_len)
{
    char result = 0;
    if (data_len <= get_queue_free_space(queue_ptr))
    {
        for(unsigned long int i = 0; i < data_len; i++)
        {
            enqueue_byte(queue_ptr, array[i]);
        }
        result = 1;
    }
    return result;
}

char dequeue_byte_array(queue_t* const queue_ptr, char* array, unsigned long int data_len)
{
    char result = 0;
    if (data_len <= get_queue_number_of_elements(queue_ptr))
    {
        for(unsigned long int i = 0; i < data_len; i++)
        {
            dequeue_byte(queue_ptr, &array[i]);
        }
        result = 1;
    }
    return result;
}

void print_queue_content(queue_t* const queue_ptr)
{
    unsigned long int numb_of_elements = get_queue_number_of_elements(queue_ptr);
    char* temp_ptr = queue_ptr->main_ptr;
    
    unsigned long int tail_ptr_index = queue_ptr->tail_ptr - queue_ptr->main_ptr;
    unsigned long int head_ptr_index = queue_ptr->head_ptr - queue_ptr->main_ptr;
    
    for(unsigned long int i = 0; i <= queue_ptr->size; i++)
    {
        if ((head_ptr_index == tail_ptr_index) &&
            (i == head_ptr_index))
        {
            if ((i == 0) || (i == queue_ptr->size))
            {
                printf(" ");
            }
            printf("HT");
        }else
        {
            if (i == head_ptr_index)
            {
                printf(" H ");
            }else
            if (i == tail_ptr_index)
            {
                printf(" T ");
            }else
            {
                printf("   ");
            }
        }
    }
    printf("\n");
    
    for(unsigned long int i = 0; i < queue_ptr->size; i++)
    {
        if ((head_ptr_index < tail_ptr_index) &&
            (i >= head_ptr_index) &&
            (i < tail_ptr_index))
        {
            printf("|%02X", *(temp_ptr++));
        }else 
        if ((head_ptr_index > tail_ptr_index) &&
            ((((i >= 0) &&
               (i <= tail_ptr_index)) || 
              ((i >= head_ptr_index) &&
               (i < queue_ptr->size)))))
        {
            printf("|%02X", *(temp_ptr++));
        }else
        {
            printf("|  ");
            temp_ptr++;
        }
    }
    printf("|\n");
}