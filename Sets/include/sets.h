#ifndef SETS_H
#define SETS_H

struct set_node
{
    const char* key;
    size_t key_len;
    struct set_node* next;
};

struct set_table
{
    struct set_node** nodes;
    size_t hashmap_size;
};

#endif 