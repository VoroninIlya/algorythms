#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct node
{
    uint8_t key;
    struct node* next;
    struct node* prev;
}node_t;

#ifdef __cplusplus
}
#endif

class Dbll_list
{
private:
    
    node_t *head;
    node_t *tail;
    uint32_t length;
    
public:
    // default constructor
    Dbll_list();
    // copy constructor
    Dbll_list(const Dbll_list &dbll_list);
    // override the assignment operator
    Dbll_list& operator= (const Dbll_list &dbll_list);
    
    // destructor
    ~Dbll_list();
    
    bool is_empty(void);
    bool add(uint8_t key);
    bool split(uint32_t split_index, Dbll_list* splited_part);
    bool merge(Dbll_list* list);
    bool insert(uint32_t index, uint8_t key);
    bool del(uint32_t index);
    bool clear(void);
    uint32_t search(uint8_t key);
    uint32_t len(void);
    uint8_t get(uint32_t index);
    
    void print(void);
};

#endif // DOUBLY_LINKED_LIST_H
