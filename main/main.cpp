#include "main.h"
#if (1 == CHECK_SORT_ALGORITHMS) 
#include "insertion_sort.h"
#include "selection_sort.h"
#include "merge_sort.h"
#include "quick_sort.h"
#endif

#if (1 == CHECK_DATA_STRUCTURES)
#include "stack.h"
#include "queue.h"
#include "doubly_linked_list.hpp"
#include "binary_tree.hpp"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "tx_api.h"

#ifdef __cplusplus
}
#endif

#define     STACK_SIZE         1024
#define     DATA_LENGTH        0
#define     MY_STACK_SIZE      0
#define     MY_QUEUE_SIZE      0

#if (1 == CHECK_SORT_ALGORITHMS)
#define     DATA_LENGTH        10
#endif
#if (1 == CHECK_DATA_STRUCTURES)
#define     DATA_LENGTH        1024
#define     MY_STACK_SIZE      7
#define     MY_QUEUE_SIZE      7
#endif

#define     BYTE_POOL_SIZE     (STACK_SIZE*2 + DATA_LENGTH*2 + \
                                MY_STACK_SIZE + MY_QUEUE_SIZE)

#define     DEBUG_PRINTF       (1)

TX_THREAD     main_thread;
TX_BYTE_POOL  main_pool;

static void  main_thread_entry(ULONG thread_input);
static void  print_array(CHAR* array_ptr, ULONG array_len);
static ULONG get_memory_available(void);

#if (1 == CHECK_SORT_ALGORITHMS)
static void  check_sort_algorithm(void (*sort_algorithm)(
    char* array_ptr,
    unsigned long array_len,
    char (*condition_fn)(char, char)));
#endif

static unsigned long minimal_memory_available = 0;

#if (1 == CHECK_DATA_STRUCTURES)
static stack_t my_stack = {NULL, NULL, 0};
static queue_t my_queue = {NULL, NULL, NULL, 0};

static void check_stack(void);
static void check_queue(void);
static void check_dbll_list(void);
static void check_binary_tree(void);
#endif

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

#if (1 == CHECK_DATA_STRUCTURES)
    stack_init(&my_stack, MY_STACK_SIZE);
    unsigned long int stack_space = get_stack_free_space(&my_stack);
    printf("my_stack initialized\n");
    printf("my_stack free space: %lu\n", stack_space);
    
    queue_init(&my_queue, MY_QUEUE_SIZE);
    unsigned long int queue_space = get_queue_free_space(&my_queue);
    printf("my_queue initialized\n");
    printf("my_queue free space: %lu\n", queue_space);
#endif
}

static void  main_thread_entry(ULONG thread_input)
{
    update_minimal_memory_available();
#if (1 == CHECK_SORT_ALGORITHMS)
    check_sort_algorithm(insertion_sort);
    check_sort_algorithm(selection_sort);
    check_sort_algorithm(quick_sort);
    check_sort_algorithm(quick_sort_randomized);
    check_sort_algorithm(merge_sort);
#endif

#if (1 == CHECK_DATA_STRUCTURES)
    check_stack();
    check_queue();
    check_dbll_list();
    check_binary_tree();
    printf("Memory available: %lu\n", (unsigned long)get_memory_available());
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

#if (1 == CHECK_SORT_ALGORITHMS)
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
    }else
    if (sort_algorithm == quick_sort)
    {
        sprintf(message, "%s", "quick_sort");
    }else
    if (sort_algorithm == quick_sort_randomized)
    {
        sprintf(message, "%s", "quick_sort_randomized");
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
#endif

#if (1 == CHECK_DATA_STRUCTURES)
static void check_stack(void)
{
    char temp_arr[5] = {0x03, 0x04, 0x05, 0x06, 0x07};
    char temp_byte = 0;
    
    printf("1. Add byte to the stack:\n");
    push_byte(&my_stack, 0x01);
    print_stack_content(&my_stack);
    printf("\n");
    printf("2. Add byte to the stack:\n");
    push_byte(&my_stack, 0x02);
    print_stack_content(&my_stack);
    printf("\n");
    printf("3. Add byte array to the stack:\n");
    push_byte_array(&my_stack, temp_arr, 5);
    print_stack_content(&my_stack);
    printf("my_stack number of elements: %lu\n", get_stack_number_of_elements(&my_stack));
    printf("my_stack free space: %lu\n", get_stack_free_space(&my_stack));
    printf("\n");
    printf("4. Add byte array to the stack:\n");
    push_byte_array(&my_stack, temp_arr, 5);
    print_stack_content(&my_stack);
    printf("\n");
    printf("5. Get byte from the stack:\n");
    pop_byte(&my_stack, &temp_byte);
    print_stack_content(&my_stack);
    printf("\n");
    printf("6. Get byte from the stack:\n");
    pop_byte(&my_stack, &temp_byte);
    print_stack_content(&my_stack);
    printf("\n");
    printf("7. Get byte array from the stack:\n");
    pop_byte_array(&my_stack, temp_arr, 5);
    print_stack_content(&my_stack);
    printf("my_stack number of elements: %lu\n", get_stack_number_of_elements(&my_stack));
    printf("my_stack free space: %lu\n\n", get_stack_free_space(&my_stack));
    
    stack_deinit(&my_stack);
}

static void check_queue(void)
{
    char temp_arr[5] = {0x03, 0x04, 0x05, 0x06, 0x07};
    char temp_byte = 0;
    
    printf("1. Add byte to the queue:\n");
    enqueue_byte(&my_queue, 0x01);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("2. Add byte to the queue:\n");
    enqueue_byte(&my_queue, 0x02);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("3. Add byte array to the queue:\n");
    enqueue_byte_array(&my_queue, temp_arr, 5);
    print_queue_content(&my_queue);
    printf("my_queue number of elements: %lu\n", get_queue_number_of_elements(&my_queue));
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("4. Get byte from the queue:\n");
    dequeue_byte(&my_queue, &temp_byte);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("5. Add byte to the queue:\n");
    enqueue_byte(&my_queue, 0x06);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("6. Get byte from the queue:\n");
    dequeue_byte(&my_queue, &temp_byte);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("7. Get byte array from the queue:\n");
    dequeue_byte_array(&my_queue, temp_arr, 5);
    print_queue_content(&my_queue);
    printf("my_queue number of elements: %lu\n", get_queue_number_of_elements(&my_queue));
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("8. Add byte array to the queue:\n");
    enqueue_byte(&my_queue, 0x07);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("9. Add byte array to the queue:\n");
    enqueue_byte(&my_queue, 0x08);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    printf("10. Get byte from the queue:\n");
    dequeue_byte(&my_queue, &temp_byte);
    print_queue_content(&my_queue);
    printf("my_queue free space: %lu\n\n", get_queue_free_space(&my_queue));
    
    queue_deinit(&my_queue);
}

static void check_dbll_list(void)
{
    Dbll_list* dbll_list = new Dbll_list;
    Dbll_list* dbll_list_1 = new Dbll_list;
    
    printf("Memory available: %lu\n", (unsigned long)get_memory_available());
    
    dbll_list->print();
    dbll_list->insert(2, 0x01);
    printf("dbll_list->insert(2, 0x01); Memory available: %lu\n", (unsigned long)get_memory_available());
    dbll_list->add(0x02);
    printf("dbll_list->add(0x02); Memory available: %lu\n", (unsigned long)get_memory_available());
    dbll_list->add(0x03);
    printf("dbll_list->add(0x03); Memory available: %lu\n", (unsigned long)get_memory_available());
    dbll_list->add(0x04);
    printf("dbll_list->add(0x04); Memory available: %lu\n", (unsigned long)get_memory_available());
    dbll_list->add(0x05);
    printf("dbll_list->add(0x05); Memory available: %lu\n", (unsigned long)get_memory_available());
    dbll_list->split(3, dbll_list_1);
    printf("dbll_list->split(3, dbll_list_1); Memory available: %lu\n", (unsigned long)get_memory_available());

    dbll_list_1->merge(dbll_list);
    printf("dbll_list_1->merge(dbll_list); Memory available: %lu\n", (unsigned long)get_memory_available());
    
    delete(dbll_list);
    printf("delete(dbll_list); Memory available: %lu\n\n", (unsigned long)get_memory_available());
    
    dbll_list_1->insert(2,0x10);
    printf("dbll_list_1->insert(2,0x10); Memory available: %lu\n", (unsigned long)get_memory_available());
    dbll_list_1->del(4);
    printf("dbll_list_1->del(4); Memory available: %lu\n\n", (unsigned long)get_memory_available());
    dbll_list_1->print();
    
    printf("dbll_list_1->get(2): %lu\n", (unsigned long)dbll_list_1->get(2));
    printf("dbll_list_1->get(5): %lu\n\n", (unsigned long)dbll_list_1->get(5));
    
    printf("dbll_list_1->search(16): %lu\n", (unsigned long)dbll_list_1->search(16));
    printf("dbll_list_1->search(1): %lu\n\n", (unsigned long)dbll_list_1->search(1));
    
    delete(dbll_list_1);
    printf("delete(dbll_list_1); Memory available: %lu\n\n", (unsigned long)get_memory_available());
}

static void check_binary_tree(void)
{
    Binary_tree tree_1;
    
    printf("Memory available: %lu\n", (unsigned long)get_memory_available());
    
    tree_1.insert(Binary_tree_node(uint32_t(3)));
    printf("tree_1.insert(3); Memory available: %lu\n", (unsigned long)get_memory_available());
    tree_1.insert(Binary_tree_node(uint32_t(1)));
    printf("tree_1.insert(1); Memory available: %lu\n", (unsigned long)get_memory_available());
    tree_1.insert(Binary_tree_node(uint32_t(2)));
    printf("tree_1.insert(2); Memory available: %lu\n", (unsigned long)get_memory_available());
    tree_1.insert(Binary_tree_node(uint32_t(10)));
    printf("tree_1.insert(10); Memory available: %lu\n", (unsigned long)get_memory_available());
    tree_1.insert(Binary_tree_node(uint32_t(4)));
    printf("tree_1.insert(4); Memory available: %lu\n", (unsigned long)get_memory_available());
    tree_1.insert(Binary_tree_node(uint32_t(0)));
    printf("tree_1.insert(0); Memory available: %lu\n", (unsigned long)get_memory_available());
    tree_1.insert(Binary_tree_node(uint32_t(5)));
    printf("tree_1.insert(5); Memory available: %lu\n", (unsigned long)get_memory_available());
    
    tree_1.print();
    
    tree_1.del(tree_1.search(4));
    printf("tree_1.del(4); Memory available: %lu\n", (unsigned long)get_memory_available());

    tree_1.del(tree_1.search(1));
    printf("tree_1.del(1); Memory available: %lu\n", (unsigned long)get_memory_available());
    
    tree_1.del(tree_1.search(3));
    printf("tree_1.del(3); Memory available: %lu\n", (unsigned long)get_memory_available());
    
    tree_1.print();
    
    
    printf("tree_1.search(2).print():\n");
    tree_1.search(2).print();
    printf("\n");
    printf("tree_1.search(100).print():\n");
    tree_1.search(100).print();
    printf("\n");
    printf("tree_1.maximum().print():\n");
    tree_1.maximum(tree_1.get_root()).print();
    printf("\n");
}
#endif 

static ULONG get_memory_available(void)
{
    ULONG available = 0;
    tx_byte_pool_info_get(&main_pool, NULL, &available, NULL, NULL, NULL, NULL);
    return available;
}

#ifdef __cplusplus
extern "C" {
#endif

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
    ULONG available = get_memory_available();

    if(minimal_memory_available > available)
    {
        minimal_memory_available = available;
    }
}

#ifdef __cplusplus
}
#endif