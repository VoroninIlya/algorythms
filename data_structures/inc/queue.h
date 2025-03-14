#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

typedef void* (*queue_allocCb_t)(size_t size);
typedef void (*queue_freeCb_t)(void* mem_ptr);

typedef struct {
    char* main_ptr;
    char* head_ptr;
    char* tail_ptr;
    unsigned long int size;
    queue_allocCb_t allocCb;
    queue_freeCb_t freeCb;
}queue_t;

void queue_set_alloc_cb(queue_t* const queue_ptr, queue_allocCb_t alcb);
void queue_set_free_cb(queue_t* const queue_ptr, queue_freeCb_t alcb);

void queue_init(queue_t* const queue_ptr, unsigned long int size);
void queue_deinit(queue_t* const queue_ptr);
char is_queue_empty(queue_t* const queue_ptr);
unsigned long int get_queue_number_of_elements(queue_t* const queue_ptr);
unsigned long int get_queue_free_space(queue_t* const queue_ptr);
char enqueue_byte(queue_t* const queue_ptr, char byte);
char dequeue_byte(queue_t* const queue_ptr, char* byte);
char enqueue_byte_array(queue_t* const queue_ptr, char* array, unsigned long int data_len);
char dequeue_byte_array(queue_t* const queue_ptr, char* array, unsigned long int data_len);
void print_queue_content(queue_t* const queue_ptr);

#ifdef __cplusplus
}
#endif

#endif // QUEUE_H