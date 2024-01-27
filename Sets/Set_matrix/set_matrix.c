#include <stddef.h>
#include <string.h>
#include <stdio.h>

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
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

// Function to check if a key is already in the set
int set_item_check(struct set* set, const char* key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if(set->hashmap[index][i].key_len > 0)
        {
            if(set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                return 1;
            }        
        }    
        
    }

    return 0;
}

// Function to insert a key in the set
void set_insert(struct set* set, const char* key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s: %llu (index: %llu)\n", key, hash, index);

    // If the first cell at index, coming out from hashing, is empty, we can insert the item 
    if(set->hashmap[index][0].key_len == 0)
    {
        set->hashmap[index][0].key = key;
        set->hashmap[index][0].key_len = key_len;
        printf("Added %s at index %llu slot 0\n", key, index);
        return;
    }

    // If the first cell at index, coming out from hashing, is already full, then we have a Collision
    if(set->hashmap[index][0].key_len > 0)
    {
        printf("COLLISION! for %s (index %llu)\n", key, index);
        for(size_t i = 1; i < HASHMAP_SIZE_LIST; i++)
        {   // Here we check if a key is already in the set
            if(set_item_check(set, key))
            {
                printf("%s already in set\n", key);
                return;
            }
            // ...otherwise we insert the item...
            if(set->hashmap[index][i].key_len == 0)
            {
                set->hashmap[index][i].key = key;
                set->hashmap[index][i].key_len = key_len;
                printf("Added %s at index %llu slot %llu\n", key, index, i);
                return;
            }
            // ...until the set is full and we can't insert the item
            if(set->hashmap[index][i].key_len > 0 && (i == HASHMAP_SIZE_LIST - 1))
            {
                printf("index %llu Complete - No place for %s!!!\n", index, key);
            }
        }
    }
   
}

// Function to find a key in the set
void set_find(struct set* set, const char* key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s: %llu (index: %llu)\n", key, hash, index);

    for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if(set->hashmap[index][i].key_len > 0)
        {
            // If the keys have the same lenght and the comparison is equal to 0, we found the key
            if(set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("Found %s at index %llu slot %llu\n", key, index, i);
                return;
            }        
        }    
        
    }

    printf("Not Found %s in Set\n", key);
}

// Function to remove a key from the set
void set_remove(struct set* set, const char* key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s: %llu (index: %llu)\n", key, hash, index);

    for(size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if(set->hashmap[index][i].key_len > 0)
        {
            if(set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
            {
                printf("Found and Removed %s at index %llu slot %llu\n", key, index, i);
                
                // If the key to remove is in the set, we consider three situations
                for(size_t j = i; j < HASHMAP_SIZE_LIST; j++)
                {
                    // There's not a key after the key to remove or the key to remove is the last element of the list
                    if(set->hashmap[index][j + 1].key_len == 0 || j == (HASHMAP_SIZE_LIST - 1))
                    {
                        set->hashmap[index][j].key = NULL;
                        set->hashmap[index][j].key_len = 0;
                        return;
                    }               
                    // There's a key after the key to remove and it's the last key of the list
                    else if(set->hashmap[index][j + 1].key_len > 0 && (j + 1) == (HASHMAP_SIZE_LIST - 1))
                    {
                        set->hashmap[index][j].key = set->hashmap[index][j + 1].key;
                        set->hashmap[index][j].key_len = set->hashmap[index][j + 1].key_len;
                        set->hashmap[index][j + 1].key = NULL;
                        set->hashmap[index][j + 1].key_len = 0;  
                        return;                      
                    }
                    // There's a key after the key to remove
                    else if(set->hashmap[index][j + 1].key_len > 0)
                    {
                        set->hashmap[index][j].key = set->hashmap[index][j + 1].key;
                        set->hashmap[index][j].key_len = set->hashmap[index][j + 1].key_len;
                    }
                    
                }
                return;
            }        
        }            
    }

    printf("Not Found %s in Set\n", key);
}





int main(int argc, char** argv)
{
    struct set mySet;

    memset(&mySet, 0, sizeof(struct set));

    // Insert
    set_insert(&mySet, "Ciao");
    set_insert(&mySet, "Hello");
    set_insert(&mySet, "Test");
    set_insert(&mySet, "Pippo");
    set_insert(&mySet, "Parenzo");
    set_insert(&mySet, "Topolino");
    set_insert(&mySet, "Hotel");

    printf("\n");

    // Trying to insert a key already in the set
    set_insert(&mySet, "Pippo");    
    set_insert(&mySet, "Test");
    printf("\n");

    // Trying to find a key in the set
    set_find(&mySet, "Ciao");
    set_find(&mySet, "Pluto");
    set_find(&mySet, "Test");
    printf("\n");

    // Removing a key from the set and trying to find the same key after the removal. Checking if the key after takes the place of the removed key
    set_remove(&mySet, "Hello");
    set_find(&mySet, "Hello");
    set_find(&mySet, "Parenzo");
    printf("\n");

    // Inserting the same key again and checking if it's in the set, but in a different position as before
    set_insert(&mySet, "Hello");
    set_find(&mySet, "Hello");
    printf("\n");

    // Removing the key, current head of the list, and checking if the key after becomes the new head
    set_remove(&mySet, "Ciao");
    set_find(&mySet, "Parenzo");
    set_find(&mySet, "Hello");
    printf("\n");

    // Inserting the key that was the previous head again, and checking if it is stored in the last slot
    set_insert(&mySet, "Ciao");
    set_find(&mySet, "Ciao");
    printf("\n");

    return 0;
}