#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>

#define assert(cond, message) \
do \
{ \
    if (0 == cond) \
    { \
        printf("Assert: %s\n", message); \
        while(1){;} \
    }\
} while(0)
    
void* my_malloc(size_t size);
void my_free(void* mem_ptr);
void update_minimal_memory_available(void);

#endif // MAIN_H
