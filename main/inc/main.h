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

#endif // MAIN_H