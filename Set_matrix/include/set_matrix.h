#ifndef SET_MATRIX_H
#define SET_MATRIX_H

// These are the dimensions of our set
#define HASHMAP_SIZE 3
#define HASHMAP_SIZE_LIST 3


// This is the item
struct set_item
{
    const char* key;
    size_t key_len;
};

// Structure of our set
struct set
{
    struct set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
};

// Hashing Algorithm
size_t djb33x_hash(const char *key, const size_t keylen);

// Function to check if a key is already in the set
int set_item_check(struct set* set, const char* key);

// Function to insert a key in the set
void set_insert(struct set* set, const char* key);

// Function to find a key in the set
void set_find(struct set* set, const char* key);

// Function to remove a key from the set
void set_remove(struct set* set, const char* key);
#endif //SET_MATRIX_H