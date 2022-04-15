#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* main_ptr;
    char* top_ptr;
    unsigned long int size;
}stack_t;

void stack_init(stack_t* const stack_ptr, unsigned long int size);
void stack_deinit(stack_t* const stack_ptr);
char is_stack_empty(stack_t* const stack_ptr);
unsigned long int get_stack_number_of_elements(stack_t* const stack_ptr);
unsigned long int get_stack_free_space(stack_t* const stack_ptr);
char push_byte(stack_t* const stack_ptr, char byte);
char pop_byte(stack_t* const stack_ptr, char* byte);
char push_byte_array(stack_t* const stack_ptr, char* array, unsigned long int data_len);
char pop_byte_array(stack_t* const stack_ptr, char* array, unsigned long int data_len);
void print_stack_content(stack_t* const stack_ptr);

#ifdef __cplusplus
}
#endif

#endif // STACK_H
