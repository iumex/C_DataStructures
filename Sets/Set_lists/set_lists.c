#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;
    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }
    return hash;
}

// Function to create our set
struct set_table* set_table_init(const size_t hashmap_size)
{
    struct set_table* table = malloc(sizeof(struct set_table));

    if(!table)
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;

    table->nodes = calloc(table->hashmap_size, sizeof(struct set_node*));

    if(!table->nodes)
    {
        free(table);
        return NULL;
    }

    
    return table;
}

// Function to insert a key in the set
struct set_node* set_insert(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct set_node* head = table->nodes[index];

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    // The list at index, coming from hash, is still empty
    if(!head)
    {
        table->nodes[index] = malloc(sizeof(struct set_node));
        //printf("Head = %s\n", key);

        if(!table->nodes[index])
        {
            printf("Impossible to allocate space for the new head!!!");
            return NULL;
        }

        table->nodes[index]->key = key;         
        table->nodes[index]->key_len = key_len;
        table->nodes[index]->next = NULL;
        printf("Added %s at index %llu\n", key, index);

        return table->nodes[index];
    }


    // The list at index, coming from hash, contains elements already
    printf("COLLISION! for %s (index %llu)\n", key, index);

    struct set_node* new_item = malloc(sizeof(struct set_node));
    
    if(!new_item)
    {
        printf("Impossible to allocate space for the new item!!!");
        return NULL;
    }

    new_item->key = key;
    new_item->key_len = key_len;
    new_item->next = NULL;

    struct set_node* tail = head;


    while(head)
    {
        tail = head;
        head = head->next;
    }
    tail->next = new_item;
    printf("Added %s at index %llu\n", key, index);
    
    //return new_item;
    return table->nodes[index];
}


// Function to find an element in the set
int set_find(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    struct set_node* current_node = table->nodes[index];
    struct set_node* last_node = NULL;

    while(current_node)
    {
        if(current_node->key_len == key_len && !memcmp(current_node->key, key, sizeof(char*)))
        {
            printf("Found key: %s\n", key);
            return 1;
        }
        else
        {
            last_node = current_node;
            current_node = current_node->next;
        }
    }

    printf("Key %s is not in the set!!!\n", key);

    return 0;
}

//Function to remove an element from the set
struct set_node* remove_item(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct set_node* previous_node = NULL;
    struct set_node* current_node = table->nodes[index];
    struct set_node* next_node = NULL;

    // The node to remove is the head of the linked list
    if(current_node->key_len == key_len && !memcmp(current_node->key, key, sizeof(char*)))
    {
        table->nodes[index] = table->nodes[index]->next;
        current_node->next = NULL;
        free(current_node);

        return table->nodes[index];
    }

    // The node to remove is not the head of the linked list
    while(current_node)
    {
        if(current_node->key_len == key_len && !memcmp(current_node->key, key, sizeof(char*)))
        {
            next_node = current_node->next;
            previous_node->next = next_node;
            current_node->next = NULL;
            free(current_node);

            return table->nodes[index];
        }

        previous_node = current_node;
        current_node = current_node->next;
    }

    printf("Key %s is not in the set!!!\n", key);

    return table->nodes[index];
}

// Function to check if a key is already in the set. If not, the key is inserted in the set
struct set_node* unique_key(struct set_table* table, const char* key)
{
    const size_t key_len = strlen(key);

    size_t hash = djb33x_hash(key, key_len);

    size_t index = hash % table->hashmap_size;

    struct set_node* head = table->nodes[index];

    if(set_find(table, key))
    {
        printf("key %s is already in the set!!!\n", key);
    }
    else
    {
        printf("Inserting key %s in the set!!!\n", key);
        head = set_insert(table, key);
        return head;
    }

    return head;    
}


int main(int argc, char** argv)
{
    size_t hashmap_size = 3;
    struct set_table* table = set_table_init(hashmap_size);

    // Inserting some elements
    set_insert(table, "Ciao");
    set_insert(table, "Pippo");
    set_insert(table, "Pluto");
    set_insert(table, "Hello");
    set_insert(table, "Sandokan");
    set_insert(table, "Goldrake");

    printf("\n");

    // Trying to find different keys
    set_find(table, "Pluto");
    set_find(table, "Pippo");
    set_find(table, "Alberto");

    // Removing elements and trying to find them in the set
    printf("\n");
    remove_item(table, "Ciao");
    set_find(table, "Ciao");

    printf("\n");
    remove_item(table, "Pippo");
    set_find(table, "Pippo");

    // Checking if a key is already or not in the set
    // 1: Key is already in the set
    printf("\n");
    unique_key(table, "Hello");

    // 2: Key is not in the set and it's inserted in the set
    printf("\n");
    unique_key(table, "Cake");
   
    return 0;
}