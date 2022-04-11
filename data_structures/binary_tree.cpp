#include "binary_tree.hpp"
#include "main.h"

// =========================================================================
// class Binary_tree_node
// =========================================================================

Binary_tree_node::Binary_tree_node()
{
    this->key = 0;
    this->parent = NULL;
    this->l_child = NULL;
    this->r_child = NULL;
    this->shadow_flag = false;
}

Binary_tree_node::Binary_tree_node(bool)
{
    Binary_tree_node();
    this->shadow_flag = true;
}

// Copy constructor
Binary_tree_node::Binary_tree_node(const Binary_tree_node &n)
{
    *this = n;
}

Binary_tree_node::Binary_tree_node(uint32_t key)
{
    this->key = key;
    this->parent = NULL;
    this->l_child = NULL;
    this->r_child = NULL;
    this->shadow_flag = false;
}

Binary_tree_node::Binary_tree_node(
    uint32_t key, Binary_tree_node* parent, 
    Binary_tree_node* l_child, Binary_tree_node* r_child)
{
    this->key = key;
    this->parent = parent;
    this->l_child = l_child;
    this->r_child = r_child;
    this->shadow_flag = false;
} 

Binary_tree_node& Binary_tree_node::operator= (const Binary_tree_node &n)
{
    this->key = n.key;
    this->parent = n.parent;
    this->l_child = n.l_child;
    this->r_child = n.r_child;
    this->shadow_flag = n.shadow_flag;
    return *this;
}

bool Binary_tree_node::operator> (const Binary_tree_node &n)
{
    return this->key > n.key;
}

bool Binary_tree_node::operator<= (const Binary_tree_node &n)
{
    return !(*this > n);
}

bool Binary_tree_node::operator< (const Binary_tree_node &n)
{
    return this->key < n.key;
}

bool Binary_tree_node::operator>= (const Binary_tree_node &n)
{
    return !(*this < n);
}

bool Binary_tree_node::operator== (const Binary_tree_node &n)
{
    return this->key == n.key;
}

bool Binary_tree_node::operator!= (const Binary_tree_node &n)
{
    return !(*this == n);
}

uint32_t Binary_tree_node::get_key(void) const
{
    return this->key;
}

void Binary_tree_node::set_key(uint32_t key)
{
    this->key = key;
}

Binary_tree_node* Binary_tree_node::get_parent(void) const
{
    return this->parent;
}

void Binary_tree_node::set_parent(Binary_tree_node* node)
{
    this->parent = node;
}

Binary_tree_node* Binary_tree_node::get_l_child(void) const
{
    return this->l_child;
}

void Binary_tree_node::set_l_child(Binary_tree_node* node)
{
    this->l_child = node;
}

Binary_tree_node* Binary_tree_node::get_r_child(void) const
{
    return this->r_child;
}

void Binary_tree_node::set_r_child(Binary_tree_node* node)
{
    this->r_child = node;
}

void Binary_tree_node::print(void) const
{
    if (false == this->shadow_flag)
    {
        printf("key: %d\n", this->key);
        printf("parent: %08X\n", (unsigned int)(uintptr_t)this->parent);
        printf("l_child: %08X\n", (unsigned int)(uintptr_t)this->l_child);
        printf("r_child: %08X\n", (unsigned int)(uintptr_t)this->r_child);
    }else
    {
        printf("Thsi is a shadow node\n");
    }
}

bool Binary_tree_node::is_shadow(void) const
{
    return this->shadow_flag;
}

// =========================================================================
// class Binary_tree
// =========================================================================

Binary_tree::Binary_tree()
{
    this->root = NULL;
    
    Binary_tree_node tmp_shadow_node(true);
    this->shadow_node = (Binary_tree_node*)my_malloc(sizeof(tmp_shadow_node));
    *this->shadow_node = tmp_shadow_node;
}

Binary_tree::~Binary_tree()
{
    this->inorder_tree_walk(this->root, Binary_tree::delete_fn);
    
    my_free((void*)this->shadow_node);
    this->shadow_node = NULL;
}

void Binary_tree::print_fn(Binary_tree_node* n)
{
    n->print();
}

void Binary_tree::delete_fn(Binary_tree_node* n)
{
    my_free((void*)n);
    n = NULL;
}

void Binary_tree::inorder_tree_walk(
    Binary_tree_node* node, 
    void (*fn_cb)(Binary_tree_node*))
{
    if (NULL != node)
    {
        this->inorder_tree_walk(node->get_l_child(), fn_cb);
        if (NULL != fn_cb)
        {
            fn_cb(node);
        }
        this->inorder_tree_walk(node->get_r_child(), fn_cb);
    }
}

Binary_tree_node* Binary_tree::search_recursive(
    const Binary_tree_node* n, 
    const uint32_t key)
{
    Binary_tree_node* result = NULL;
    
    if (NULL != n)
    {
        if (key == n->get_key())
        {
            return (Binary_tree_node*)(n);
        }
        if (key < n->get_key())
        {
            return (Binary_tree_node*)(
                this->search_recursive(n->get_l_child(), key));
        }else
        {
            return (Binary_tree_node*)(
                this->search_recursive(n->get_r_child(), key));
        }
    }
    return result;
}

Binary_tree_node* Binary_tree::search_recursive(
    const Binary_tree_node* n, 
    const uint32_t key, 
    const Binary_tree_node* parent,
    const Binary_tree_node* l_child,
    const Binary_tree_node* r_child)
{   
    Binary_tree_node* result = NULL;
    
    if (NULL != n)
    {
        if ((key == n->get_key()) &&
            (parent == n->get_parent()) && 
            (l_child == n->get_l_child()) &&
            (r_child == n->get_r_child()))
        {
            return (Binary_tree_node*)n;
        }
        if (key < n->get_key())
        {
            return (Binary_tree_node*)(this->search_recursive(
                n->get_l_child(), key, parent, l_child, r_child));
        }else
        {
            return (Binary_tree_node*)(this->search_recursive(
                n->get_r_child(), key, parent, l_child, r_child));
        }
    }
    return result;
}

const Binary_tree_node& Binary_tree::get_root(void)
{
    return *(this->root);
}

const Binary_tree_node& Binary_tree::search(uint32_t key)
{
    Binary_tree_node* result = this->search_recursive(this->root, key);
    if (NULL != result)
    {
        return *result;
    }else
    {
        return *(this->shadow_node);
    }
    
}

const Binary_tree_node& Binary_tree::search(
    const uint32_t key, 
    const Binary_tree_node* parent, 
    const Binary_tree_node* l_child, 
    const Binary_tree_node* r_child)
{
    Binary_tree_node* result = this->search_recursive(
        this->root, key, parent, l_child, r_child);
    if (NULL != result)
    {
        return *result;
    }else
    {
        return *(this->shadow_node);
    }
}

const Binary_tree_node& Binary_tree::minimum(const Binary_tree_node &node)
{
    Binary_tree_node* tmp_node = this->get_node_ptr(node);
    while (NULL != tmp_node->get_l_child())
    {
        tmp_node = tmp_node->get_l_child();
    }
    return *tmp_node;
}

const Binary_tree_node& Binary_tree::maximum(const Binary_tree_node &node)
{
    Binary_tree_node* tmp_node = this->get_node_ptr(node);
    while (NULL != tmp_node->get_r_child())
    {
        tmp_node = tmp_node->get_r_child();
    }
    return *tmp_node;
}

void Binary_tree::transplant(
    Binary_tree_node* node_1, 
    Binary_tree_node* node_2)
{
    if (NULL == node_1->get_parent())
    {
        this->root = node_2;
    }else
    if (node_1 == node_1->get_parent()->get_l_child())
    {
        node_1->get_parent()->set_l_child(node_2);
    }else
    {
        node_1->get_parent()->set_r_child(node_2);
    }
    if (NULL != node_2)
    {
        node_2->set_parent(node_1->get_parent());
    }
}

void Binary_tree::insert(const Binary_tree_node &node)
{
    Binary_tree_node* tmp_node_1 = NULL; 
    Binary_tree_node* tmp_node_2 = this->root;
    
    // Allocating memory through my_malloc function instead:
    // Binary_tree_node* new_node = new Binary_tree_node(node);
    // to be able to count it by using ThreadX
    Binary_tree_node* new_node = (Binary_tree_node*)my_malloc(sizeof(node));
    *new_node = node;
    
    while(NULL != tmp_node_2)
    {
        tmp_node_1 = tmp_node_2;
        if (*tmp_node_2 > *new_node)
        {
            tmp_node_2 = tmp_node_2->get_l_child();
        }else
        {
            tmp_node_2 = tmp_node_2->get_r_child();
        }
    }
    new_node->set_parent(tmp_node_1);
    if(NULL == tmp_node_1)
    {
        this->root = new_node;
    }else
    if (*tmp_node_1 > *new_node)
    {
        tmp_node_1->set_l_child(new_node);
    }else
    {
        tmp_node_1->set_r_child(new_node);
    }
}

void Binary_tree::del(const Binary_tree_node &node)
{
    Binary_tree_node temp_node = this->search(
        node.get_key(), node.get_parent(), 
        node.get_l_child(), node.get_r_child());
    
    Binary_tree_node* curr_node_ptr = this->get_node_ptr(temp_node);

    // check if this node existiert in tree
    if (false == temp_node.is_shadow())
    {
        if ((NULL == temp_node.get_l_child()) && 
            (NULL == temp_node.get_r_child()))
        {
            Binary_tree::delete_fn(curr_node_ptr);
        }else
        if ((NULL == temp_node.get_l_child()) && 
            (NULL != temp_node.get_r_child()))
        {
            this->transplant(curr_node_ptr, curr_node_ptr->get_r_child());
            Binary_tree::delete_fn(curr_node_ptr);
        }else
        if ((NULL != temp_node.get_l_child()) && 
            (NULL == temp_node.get_r_child()))
        {
            this->transplant(curr_node_ptr, curr_node_ptr->get_l_child());
            Binary_tree::delete_fn(curr_node_ptr);
        }else
        {
            Binary_tree_node* minimum_node = this->get_node_ptr(
                this->minimum(*(curr_node_ptr->get_r_child())));
            
            if(minimum_node->get_parent() != curr_node_ptr)
            {
                this->transplant(minimum_node, minimum_node->get_r_child());
                minimum_node->set_r_child(curr_node_ptr->get_r_child());
                minimum_node->get_r_child()->set_parent(minimum_node);
            }
            this->transplant(curr_node_ptr, minimum_node);
            minimum_node->set_l_child(curr_node_ptr->get_l_child());
            minimum_node->get_l_child()->set_parent(minimum_node);

            Binary_tree::delete_fn(curr_node_ptr);
        }
    }
}

// Get pointer to the given node in this tree by using links in parent or childs
Binary_tree_node* Binary_tree::get_node_ptr(const Binary_tree_node &node)
{
    Binary_tree_node* result = NULL;
    
    if (false == node.is_shadow())
    {
        Binary_tree_node* parent = node.get_parent();
        Binary_tree_node* r_child = node.get_r_child();
        Binary_tree_node* l_child = node.get_l_child();
        if (NULL != l_child)
        {
            return l_child->get_parent();
        }else
        if (NULL != r_child)
        {
            return r_child->get_parent();
        }else
        {
            if (NULL == parent)
            {
                return this->root;
            }else
            {
                if(*parent < node)
                {
                    return parent->get_r_child();
                }else
                {
                    return parent->get_l_child();
                }
            }
        }
    }
    return result;
}

void Binary_tree::print(void)
{
    this->inorder_tree_walk(this->root, Binary_tree::print_fn);
    
}
