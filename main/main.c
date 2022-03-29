#include "main.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "merge_sort.h"
#include "tx_api.h"

#define     STACK_SIZE         1024

#define     DATA_LENGTH        10

#define     BYTE_POOL_SIZE     (STACK_SIZE*2 + DATA_LENGTH*2)

#define     DEBUG_PRINTF       (1)

TX_THREAD     main_thread;
TX_BYTE_POOL  main_pool;

static void  main_thread_entry(ULONG thread_input);
static void  print_array(CHAR* array_ptr, ULONG array_len);

static void  check_sort_algorithm(void (*sort_algorithm)(
    char* array_ptr,
    unsigned long array_len,
    char (*condition_fn)(char, char)));

static unsigned long minimal_memory_available = 0;

int main(void)
{
    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

void    tx_application_define(void *first_unused_memory)
{
    CHAR  *stack_ptr;
    ULONG available = 0;

    /* Create a byte memory pool for thread stack allocation. */
    tx_byte_pool_create(&main_pool, "main_pool",
                        first_unused_memory, BYTE_POOL_SIZE);
    
    tx_byte_pool_info_get(&main_pool, NULL, &available, NULL, NULL, NULL, NULL);
    minimal_memory_available = available;
    
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
    update_minimal_memory_available();
    check_sort_algorithm(insertion_sort);
    check_sort_algorithm(selection_sort);
    check_sort_algorithm(merge_sort);
}

static void  print_array(CHAR* array_ptr, ULONG array_len)
{
    for(ULONG index = 0; index < array_len; index++)
    {
        printf("%3d ", array_ptr[index]);
    }
    printf("\n");
}

static void  check_sort_algorithm(void (*sort_algorithm)(
    char* array_ptr,
    unsigned long array_len,
    char (*condition_fn)(char, char)))
{
    char message[255] = "Unknown";
    
    assert(sort_algorithm, "Null-pointer in check_sort_algorithm");
    
    char* input_data = my_malloc(DATA_LENGTH);
    
    // Initialize input_data
    for(ULONG index = 0; index < DATA_LENGTH; index++)
    {
        input_data[index] = rand() % 0xFF;
    }
    
#if (1 == DEBUG_PRINTF)
    printf("Input array:\n");
    print_array(input_data, DATA_LENGTH);
#endif

    if (sort_algorithm == insertion_sort)
    {
        sprintf(message, "%s", "insertion_sort");
    }else
    if (sort_algorithm == selection_sort)
    {
        sprintf(message, "%s", "selection_sort");
    }else
    if (sort_algorithm == merge_sort)
    {
        sprintf(message, "%s", "merge_sort");
    }

    printf("Start %s. Current Time: %lu\n", message, (unsigned long)(tx_time_get()));
    sort_algorithm(input_data, DATA_LENGTH, less_then);
    printf("Finish %s. Current Time: %lu\n", message, (unsigned long)(tx_time_get()));
    
#if (1 == DEBUG_PRINTF)
    printf("Output array:\n");
    print_array(input_data, DATA_LENGTH);
#endif
    printf("minimal_memory_available: %lu\n", minimal_memory_available);
    
    my_free(input_data);
}

void* my_malloc(size_t size){
    void* result = NULL;
    void* temp_pointer = NULL;
    // allocate memory
    UINT status = tx_byte_allocate(&main_pool, (VOID **) &temp_pointer,
                                   size, TX_NO_WAIT);
    if (TX_SUCCESS == status)
    {
        result = temp_pointer;
        update_minimal_memory_available();
    }else{
        printf("Error: memory allocation\n");
    }
    return result;
}
void my_free(void* mem_ptr)
{
    if (NULL != mem_ptr)
    {
        UINT status = tx_byte_release((VOID *)mem_ptr);
        if (TX_SUCCESS != status)
        {
            printf("Error: memory releasing\n");
        }
    }
}
void update_minimal_memory_available(void)
{
    ULONG available = 0;
    
    tx_byte_pool_info_get(&main_pool, NULL, &available, NULL, NULL, NULL, NULL);
    if(minimal_memory_available > available)
    {
        minimal_memory_available = available;
    }
}
