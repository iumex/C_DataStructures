#include "dict_string_int.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
} 


struct dict_table* dict_table_init(const size_t hashmap_size)
{
    struct dict_table* table = malloc(sizeof(struct dict_table));

    if(!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->number_collisions = 0;
    table->number_elements = 0;
    table->nodes = calloc(table->hashmap_size, sizeof(struct dict_node*));

    if(!table->nodes)
    {
        free(table);
        return NULL;
    }

    
    return table;
}


struct dict_table* dict_insert(struct dict_table* table, const char* key, int value)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct dict_node* head = table->nodes[index];

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    // The list at index, coming from hash, is still empty
    if(!head)
    {
        table->nodes[index] = malloc(sizeof(struct dict_node));
     
        if(!table->nodes[index])
        {
            printf("Impossible to allocate space for the new head!!!");
            return NULL;
        }

        table->nodes[index]->key = key;         
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->value = value;
        table->nodes[index]->next = NULL;
        table->number_elements++;
        printf("Added %s at index %llu\n", key, index);

        //return table->nodes[index];
        return table;
    }


    // The list at index, coming from hash, contains elements already
    printf("COLLISION! for %s (index %llu)\n", key, index);
    table->number_collisions++;

    struct dict_node* new_item = malloc(sizeof(struct dict_node));
    
    if(!new_item)
    {
        printf("Impossible to allocate space for the new item!!!");
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->value = value;
    new_item->next = NULL;
    table->number_elements++;

    struct dict_node* tail = head;


    while(head)
    {
        tail = head;
        head = head->next;
    }
    tail->next = new_item;

    printf("Added %s at index %llu\n", key, index);

    printf("\n");

    printf("Number of Collisions: %d\n", table->number_collisions);

    printf("\n");

    if(table->number_collisions >= MAX_COLLISIONS)
    {
        struct dict_node** temp_table = malloc(table->number_elements * sizeof(struct dict_node));

        if(!temp_table)
        {
            return NULL;
        }

        int temp_index = 0;


        for(size_t i = 0; i < table->hashmap_size; i++)
        {

            struct dict_node* head = table->nodes[i];             
            struct dict_node* tail = head;
        

            while(head)
            {            
                temp_table[temp_index] = head;          
                tail = head;
                head = head->next;           
                temp_index++;          
            }        
        }

        free(table);

        struct dict_table* new_table = dict_table_init(table->hashmap_size * INCREASE_RATE);

        for(int i = 0; i < temp_index; i++)
        {
            dict_insert(new_table, temp_table[i]->key, temp_table[i]->value);
        }

        free(*temp_table);
        return(new_table);
    }
    
  
    return table;
}


int find_val_by_key(struct dict_table* table, const char* key)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    struct dict_node* current_node = table->nodes[index];
    struct dict_node* last_node = NULL;


    while(current_node)
    {
        if(current_node->key_len == key_len && !memcmp(current_node->key, key, sizeof(char*)))
        {
            printf("Found key: %s, Searched Value: %d\n", key, current_node->value);
            return 1;
        }
        else
        {
            last_node = current_node;
            current_node = current_node->next;
        }
    }

    printf("Key %s not found in the dictionary!\n", key);
    return 0;
}



