#include "main.h"
#include "insertion_sort.h"
#include "tx_api.h"

#define     STACK_SIZE         1024
#define     BYTE_POOL_SIZE     4096

#define DATA_LENGTH 10

#define DEBUG_PRINTF (1)

// Bytes array to check algorythm
static CHAR input_data[DATA_LENGTH];

TX_THREAD     main_thread;
TX_BYTE_POOL  main_pool;

static void  main_thread_entry(ULONG thread_input);
static void  print_array(CHAR* array_ptr, ULONG array_len);

int main(void)
{
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

void    tx_application_define(void *first_unused_memory)
{
    CHAR    *stack_ptr;

    // Initialize input_data
    for(ULONG index = 0; index < DATA_LENGTH; index++)
    {
        input_data[index] = rand() % 0xFF;
    }
    
    /* Create a byte memory pool for thread stack allocation. */
    tx_byte_pool_create(&main_pool, "main_pool",
                        first_unused_memory, BYTE_POOL_SIZE);
    
    /* Allocate the stack for the main_thread.  */
    tx_byte_allocate(&main_pool, (VOID **) &stack_ptr,
                     STACK_SIZE, TX_NO_WAIT);
                     
    /* Create the main_thread.  */
    tx_thread_create(&main_thread, "main_thread",
                     main_thread_entry, 0,  
                     stack_ptr, STACK_SIZE, 0, 0,
                     TX_NO_TIME_SLICE, TX_AUTO_START);
}

static void  main_thread_entry(ULONG thread_input)
{
#if (1 == DEBUG_PRINTF)
    printf("Input array:\n");
    print_array(input_data, DATA_LENGTH);
#endif

    printf("Start insertion sort. Current Time: %lu\n",(unsigned long)(tx_time_get()));
    insertion_sort(input_data, DATA_LENGTH, less_then);
    printf("Finish insertion sort. Current Time: %lu\n",(unsigned long)(tx_time_get()));
    
#if (1 == DEBUG_PRINTF)
    printf("Output array:\n");
    print_array(input_data, DATA_LENGTH);
#endif
}

static void  print_array(CHAR* array_ptr, ULONG array_len)
{
    for(ULONG index = 0; index < array_len; index++)
    {
        printf("%3d ", array_ptr[index]);
    }
    printf("\n");
}

