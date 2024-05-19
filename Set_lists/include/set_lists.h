#ifndef SET_LISTS_H
#define SET_LISTS_H

// This is our node
struct set_node
{
    const char* key;
    size_t key_len;
    struct set_node *next;
};

// Structure of our set
struct set_table
{
    struct set_node** nodes;
    size_t hashmap_size;
};

// Hashing Algorithm
size_t djb33x_hash(const char *key, const size_t keylen);

// Function to create our set
struct set_table* set_table_init(const size_t hashmap_size);

// Function to insert a key in the set
struct set_node* set_insert(struct set_table* table, const char* key);

// Function to find an element in the set
int set_find(struct set_table* table, const char* key);

//Function to remove an element from the set
struct set_node* remove_item(struct set_table* table, const char* key);

// Function to check if a key is already in the set. If not, the key is inserted in the set
struct set_node* unique_key(struct set_table* table, const char* key);


#endif //SET_LISTS_H