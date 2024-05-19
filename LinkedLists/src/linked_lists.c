#include "linked_lists.h"
#include <stdio.h>
#include <stdlib.h>

// Function to get the tail of the linked list
struct list_item* list_get_tail(struct list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct list_item* current_item = *head;
    struct list_item* last_item = NULL;

    while(current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }

    return last_item;    
}

// Function to append a new element to the linked list
struct list_item* list_append(struct list_item** head, struct list_item* item)
{
    struct list_item* tail = list_get_tail(head);

    if(!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;
    return item;

}

// Lenght of the linked list
unsigned int list_lenght(struct list_item* head)
{
    return head->count;
}

// Function to pop the head of the linked list
struct list_item* list_pop(struct list_item** head)
{
    if(!*head)
    {
        return NULL;
    }

    struct list_item* current_head = *head;
    unsigned int current_count = current_head->count;
    *head = (*head)->next;

    if(*head)
    {
        (*head)->count = current_count - 1;
    }

    current_head->next = NULL;

    //return current_head;
    return *head;
    
}

// Function to add an element to the head of the list. The added element becomes the new head
struct list_item* list_add(struct list_item** head, struct list_item* item)
{
    if(!(*head))
    {
        *head = item;
        (*head)->next = NULL;       
        (*head)->count = 1;
        return item;        
    }

    unsigned int current_count = (*head)->count;
    item->next = *head;
    *head = item;
    (*head)->count = current_count + 1;

    //return item;
    return *head;
}

// Function to remove an element of the linked list, given its address
struct list_item* remove_item(struct list_item** head, struct list_item* item)
{
    if(!*head)
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
        current_item->next = NULL;
        (*head)->count = current_count - 1;

        //return current_item;        
        return *head;        
    }
    
    // The item to remove is not the head of the linked list
    while(current_item)    
    {             
        if(current_item == item)        
        {   
            next_item = current_item->next;
            previous_item->next = next_item;
            current_item->next = NULL;    
            (*head)->count = current_count - 1;          

            //return current_item;
            return *head;
        }       
       
        previous_item = current_item;
        current_item = current_item->next;        
    }
  
    //return current_item;
    return *head;
}

// Function to print the reversed list
struct list_item* reverse_list(struct list_item** head)
{
    if(!(*head))
    {
        return NULL;
    }

    struct list_item* current_item = *head;
    struct list_item* last_item = NULL;
    struct list_item* new_head = NULL;
    
    while(current_item)
    {       
        last_item = current_item;
        current_item = current_item->next;      
        list_add(&new_head, last_item);               
    }

    struct int_item* new_int_item = (struct int_item*)new_head;

    printf("Reversed List: \n");

    printf("Number of elements: %d\n", new_head->count);


    while(new_int_item)
    {
        printf("Element Value: %d\n", new_int_item->value);
        new_int_item = (struct int_item*)new_int_item->list_item.next;
    }   

    return new_head;
}







