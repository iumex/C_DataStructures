#include "set_matrix.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>




size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}


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





