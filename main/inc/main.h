#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

void* my_malloc(size_t size);
void my_free(void* mem_ptr);
void update_minimal_memory_available(void);

#ifdef __cplusplus
}
#endif

#endif // MAIN_H
