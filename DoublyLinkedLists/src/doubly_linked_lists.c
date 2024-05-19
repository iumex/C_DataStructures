#include "doubly_linked_lists.h"
#include <stddef.h>
#include <stdio.h>



struct list_item* list_get_tail(struct list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct list_item* prev_item = NULL;
    struct list_item* current_item = *head;
    struct list_item* next_item = NULL;

    while(current_item)
    {
        prev_item = current_item;
        current_item = current_item->next;
    }

    return prev_item;
}

struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(head);

    if (!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {       
        tail->next = item;
        (*head)->count++;
    }

    item->prev = tail;
    item->next = NULL;
    return item;    
}

unsigned int list_lenght(struct list_item** head)
{
    return (*head)->count;
}

struct list_item* remove_item(struct list_item** head, struct list_item* item)
{
    if(!(*head))
    {
        return NULL;
    }
    struct list_item* previous_item = NULL;
    struct list_item* current_item = *head;
    struct list_item* next_item = NULL;
    unsigned int current_count = current_item->count;

    

    // The item to remove is the head of the linked list
    if(current_item == item)
    {   
        *head = (*head)->next;
        current_item->prev = NULL;
        current_item->next = NULL;
        (*head)->count = current_count - 1;
        
        return current_item;        
    }
    
    // The item to remove is not the head of the linked list
    while(current_item)    
    {             
        if(current_item == item)        
        {   
            next_item = current_item->next;
            previous_item->next = next_item;
            if(next_item)
            {
                next_item->prev = previous_item;
            }
            current_item->next = NULL; 
            current_item->prev = NULL;           
            (*head)->count = current_count - 1;

            
            return current_item;
        }       
       
        previous_item = current_item;
        current_item = current_item->next;        
    }
  
    return current_item;    

    return NULL;
}

struct list_item* insert_after_item(struct list_item** head, struct list_item* item_to_insert, struct list_item* item)
{
    struct list_item* current_item = item;
    struct list_item* current_item_next = current_item->next;
    current_item->next = item_to_insert;
    current_item_next->prev = item_to_insert;
    item_to_insert->prev = current_item;
    item_to_insert->next = current_item_next;
    (*head)->count++;

    return item_to_insert;
}

// Insert item_to_insert before item
struct list_item* insert_before_item(struct list_item** head, struct list_item* item_to_insert, struct list_item* item)
{
    struct list_item* current_item = item;
    struct list_item* current_item_prev = current_item->prev;
    unsigned int current_count = (*head)->count;


    if(!current_item_prev)
    {
        struct list_item* current_head = *head;
        *head = item_to_insert;
        (*head)->next = current_head;
        (*head)->prev = NULL;

        if(*head)
        {
            (*head)->count = current_count + 1;
        }        
        
        return *head;
    }

    
    current_item->prev = item_to_insert;
    current_item_prev->next = item_to_insert;
    item_to_insert->prev = current_item_prev;
    item_to_insert->next = current_item;
    (*head)->count = current_count + 1;


    return item_to_insert;


}



