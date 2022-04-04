#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    char* main_ptr;
    char* head_ptr;
    char* tail_ptr;
    unsigned long int size;
}queue_t;

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

#endif // QUEUE_H