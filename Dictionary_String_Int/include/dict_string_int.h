#ifndef DICT_STRING_INT_H
#define DICT_STRING_INT_H

#define MAX_COLLISIONS 1
#define INCREASE_RATE 2

// This is our node
struct dict_node
{
    const char* key;
    size_t key_len;
    int value;
    struct dict_node *next;
};

// Structure of our dictionary
struct dict_table
{
    struct dict_node** nodes;
    size_t hashmap_size;    
    unsigned int number_elements;
    unsigned int number_collisions;
};


// Hashing Algorithm
size_t djb33x_hash(const char *key, const size_t keylen);

// Function to create our dictionary
struct dict_table* dict_table_init(const size_t hashmap_size);

// Function to insert a key and a correspondent value in the dictionary
struct dict_table* dict_insert(struct dict_table* table, const char* key, int value);

// Function to find an element given the key
int find_val_by_key(struct dict_table* table, const char* key);

#endif //DICT_STRING_INT_H