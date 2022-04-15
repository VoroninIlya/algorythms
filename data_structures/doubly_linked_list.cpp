#include "doubly_linked_list.hpp"
#include "main.h"

Dbll_list::Dbll_list()
{
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
}

Dbll_list::Dbll_list(const Dbll_list &dbll_list)
{
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
    
    *this = dbll_list;
}

Dbll_list& Dbll_list::operator= (const Dbll_list &dbll_list)
{
    if (!this->is_empty())
    {
        this->clear();
    }
    if (dbll_list.length > 0)
    {
        node_t* curr_node = dbll_list.head;
        uint32_t tmp_index = 0;
        while (tmp_index < dbll_list.length)
        {
            if (NULL != curr_node)
            {
                this->add(curr_node->key);
                curr_node = curr_node->next;
            }
            tmp_index++;
        }
    }
    return *this;
}

Dbll_list::~Dbll_list()
{
    this->clear();
}

bool Dbll_list::is_empty(void)
{
    if ((NULL == this->head) && 
        (NULL == this->tail))
    {
        return true;
    }else
    {
        return false;
    }
}

bool Dbll_list::add(uint8_t key)
{
    bool result = false;
    // reserve memory for new node
    node_t* new_node = (node_t*)my_malloc(sizeof(node_t));
    if (NULL != new_node)
    {
        new_node->key = key;
        new_node->next = NULL;
        if (this->is_empty())
        {
            this->head = new_node;
            this->head->prev = NULL;
            this->tail = this->head;
        }else
        {
            new_node->prev = this->tail;
            new_node->prev->next = new_node;
            this->tail = new_node;
        }
        this->length++;
        result = true;
    }
    return result;
}

bool Dbll_list::split(
    uint32_t split_index, 
    Dbll_list* splited_part)
{
    if (0 == split_index) 
    {
        *splited_part = *this;
        this->clear();
    }else
    if ((0 < split_index) &&
        (this->length > split_index))
    {
        splited_part->clear();
        node_t* curr_node = this->head;
        uint32_t tmp_index = 0;
        uint32_t tmp_length = this->length - 1;
        while (tmp_index <= tmp_length)
        {
            if (NULL != curr_node)
            {
                if (split_index == tmp_index)
                {
                    this->tail = curr_node;
                    splited_part->head = curr_node->next;
                    splited_part->head->prev = NULL;
                    curr_node = splited_part->head;
                    this->tail->next = NULL;
                    this->length = split_index + 1;
                    splited_part->length = tmp_length - split_index;
                }
                if ((tmp_length - 1) == tmp_index)
                {
                    splited_part->tail = curr_node;
                }
                curr_node = curr_node->next;
            }
            tmp_index++;
        }
    }
    return true;
}

bool Dbll_list::merge(Dbll_list* list)
{
    if (!list->is_empty())
    {
        if (!this->is_empty())
        {
            this->tail->next = list->head;
            this->tail->next->prev = this->tail;
            this->tail = list->tail;
        }else
        {
            this->head = list->head;
            this->tail = list->tail;
        }
        this->length = this->length + list->length;
        
        list->head = NULL;
        list->tail = NULL;
        list->length = 0;
    }
    return true;
}

bool Dbll_list::insert(uint32_t index, uint8_t key)
{
    bool result = false;
    
    // if index out of range the list, 
    // fill list with 0 keys until the given index is reached
    if (this->length < index)
    {
        uint32_t temp_length = this->length;
        for (uint32_t i = temp_length; i <= (index - temp_length); i++)
        {
            if (i == index)
            {
                this->add(key);
            }else
            {
                this->add(0);
            }
        }
    }else
    {
        Dbll_list tmp_dbll_list;
        this->split(index-1, &tmp_dbll_list);
        this->add(key);
        this->merge(&tmp_dbll_list);
    }
    
    return result;
}

bool Dbll_list::del(uint32_t index)
{
    Dbll_list tmp_dbll_list_1, tmp_dbll_list_2;
    
    this->split(index+1, &tmp_dbll_list_2);
    this->split(index, &tmp_dbll_list_1);
    this->merge(&tmp_dbll_list_2);
    
    return true;
}

bool Dbll_list::clear(void)
{
    if (!this->is_empty())
    {
        node_t* curr_node = this->tail;
        while(NULL != curr_node)
        {
            this->tail = curr_node->prev;
            if (NULL != this->tail)
            {
                this->tail->next = NULL;
            }
            my_free((void*)curr_node);
            curr_node = this->tail;
        }
        this->head = this->tail = NULL;
        this->length = 0;
    }
    return true;
}

uint32_t Dbll_list::search(uint8_t key)
{
    uint32_t result = 0;
    if (!this->is_empty())
    {
        node_t* curr_node_1 = this->head;
        node_t* curr_node_2 = this->tail;
        uint32_t tmp_index = 0;
        
        // search from the head and from the tail in parallel
        while ((this->length/2) >= tmp_index)
        {
           if(curr_node_1->key == key){
               result = tmp_index;
               break;
           }
           if(curr_node_2->key == key){
               result = this->length - 1 - tmp_index;
               break;
           }
           curr_node_1 = curr_node_1->next;
           curr_node_2 = curr_node_2->prev;
           tmp_index++;
        }
        
    }
    return result;
}

uint32_t Dbll_list::len(void)
{
    return this->length;
}

uint8_t Dbll_list::get(uint32_t index)
{
    uint8_t result = 0;
    if (this->length > index)
    {
        node_t* curr_node = NULL;
        uint32_t tmp_index = 0;
        
        // if index < this->length/2 search in first half from the head
        if((this->length/2) > index)
        {
            tmp_index = 0;
            curr_node = this->head;
            while (tmp_index != index)
            {
                curr_node = curr_node->next;
                tmp_index++;
            }
        // else search in second half from the tail
        }else
        {
            tmp_index = (this->length - 1);
            curr_node = this->tail;
            while (tmp_index != index)
            {
                curr_node = curr_node->prev;
                tmp_index--;
            }
        }
        result = curr_node->key;
    }
    return result;
}

void Dbll_list::print(void)
{
    if (!this->is_empty())
    {
        node_t* curr_node = this->head;
        uint32_t index = 0;
        
        printf("this->head->prev: %08X\n",  
            (unsigned int)(uintptr_t)(this->head->prev));
        printf("this->head->next: %08X\n", 
            (unsigned int)(uintptr_t)(this->head->next));
        printf("this->head->key: %d\n\n", this->head->key);
        
        while(NULL != curr_node)
        {
            printf("node[%d]->prev: %08X\n", index, 
                (unsigned int)(uintptr_t)(curr_node->prev));
            printf("node[%d]->next: %08X\n", index, 
                (unsigned int)(uintptr_t)(curr_node->next));
            printf("node[%d]->key: %d\n\n", index, curr_node->key);
            index++;
            curr_node = curr_node->next;
        }
        
        printf("this->tail->prev: %08X\n",  
            (unsigned int)(uintptr_t)(this->tail->prev));
        printf("this->tail->next: %08X\n", 
            (unsigned int)(uintptr_t)(this->tail->next));
        printf("this->tail->key: %d\n\n", this->tail->key);
    }else
    {
        printf("List is emplty.\n");
    }
}
