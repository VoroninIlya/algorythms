#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdint.h>

// =========================================================================
// class Binary_tree_node
// =========================================================================

class Binary_tree_node
{
private:
    uint32_t key;
    Binary_tree_node* parent;
    Binary_tree_node* l_child;
    Binary_tree_node* r_child;
    bool shadow_flag;

public:
    // constructors
    Binary_tree_node();
    Binary_tree_node(const Binary_tree_node&);
    Binary_tree_node(uint32_t);
    Binary_tree_node(bool); // to create shadow node
    Binary_tree_node(uint32_t, Binary_tree_node*, 
                     Binary_tree_node*,Binary_tree_node*);
    
    // overridden operators
    Binary_tree_node& operator= (const Binary_tree_node &n);
    
    bool operator> (const Binary_tree_node&);
    bool operator<= (const Binary_tree_node&);
    bool operator< (const Binary_tree_node&);
    bool operator>= (const Binary_tree_node&);
    bool operator== (const Binary_tree_node&);
    bool operator!= (const Binary_tree_node&);
    
    // getters
    uint32_t get_key(void) const;
    Binary_tree_node* get_parent(void) const;
    Binary_tree_node* get_l_child(void) const;
    Binary_tree_node* get_r_child(void) const;
    bool is_shadow(void) const;
    
    // setters
    void set_key(uint32_t);
    void set_parent(Binary_tree_node*);
    void set_l_child(Binary_tree_node*);
    void set_r_child(Binary_tree_node*);
    
    //
    void print(void) const;
};

// =========================================================================
// class Binary_tree
// =========================================================================

class Binary_tree
{
private:
    Binary_tree_node* root;
    Binary_tree_node* shadow_node;
    
    // Block copy constructor
    Binary_tree(const Binary_tree &tree){}
    // Block operator=
    Binary_tree& operator= (const Binary_tree &tree){return *this;}
    
    void inorder_tree_walk(
        Binary_tree_node* node,            // start node
        void (*fn_cb)(Binary_tree_node*)); // action function callback
    
    Binary_tree_node* search_recursive(
        const Binary_tree_node*, 
        const uint32_t);
    
    Binary_tree_node* search_recursive(
        const Binary_tree_node*, 
        const uint32_t, 
        const Binary_tree_node*,
        const Binary_tree_node*,
        const Binary_tree_node*);
    
    void transplant(
        Binary_tree_node*, 
        Binary_tree_node*);
        
    Binary_tree_node* get_node_ptr(const Binary_tree_node &node);
    
    static void print_fn(Binary_tree_node* n);
    static void delete_fn(Binary_tree_node* n);
    
public:
    Binary_tree();
    
    ~Binary_tree();
    
    const Binary_tree_node& get_root(void);
    const Binary_tree_node& search(const uint32_t);
    const Binary_tree_node& search(
        const uint32_t, 
        const Binary_tree_node*, 
        const Binary_tree_node*, 
        const Binary_tree_node*);
    const Binary_tree_node& minimum(const Binary_tree_node&);
    const Binary_tree_node& maximum(const Binary_tree_node&);
    
    void insert(const Binary_tree_node &node);
    void del(const Binary_tree_node &node);
    
    void print(void);
};

#endif // BINARY_TREE_H
