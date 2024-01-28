#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct list_item
{
    struct list_item* next;      
    unsigned int count;
};

struct int_item
{
    struct list_item list_item;
    int value;
};

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

    while(new_int_item)
    {
        printf("Element Value: %d\n", new_int_item->value);
        new_int_item = (struct int_item*)new_int_item->list_item.next;
    }   

    return new_head;
}


int main(int argc, char** argv)
{
    printf("\n");
    // head of the linked list set to NULL
    struct list_item* head = NULL;

    //-------------------------------------------------------------------------------------------------------------------------------------------    
    printf("Appending Elements\n");

    // Appending 4 elements to the linked list
    struct int_item int_item1;
    int_item1.value = 100;
    list_append(&head, (struct list_item*)&int_item1);

    struct int_item int_item2;
    int_item2.value = 200;
    list_append(&head, (struct list_item*)&int_item2);

    struct int_item int_item3;
    int_item3.value = 300;
    list_append(&head, (struct list_item*)&int_item3);

    struct int_item int_item4;
    int_item4.value = 400;
    list_append(&head, (struct list_item*)&int_item4);
 

    // int_item becomes the head of the linked list
    struct int_item* int_item = (struct int_item*)head;

    // Calculating the lenght of the linked list
    unsigned int len = list_lenght((struct list_item*)int_item);
    printf("Number of elements: %d\n", len);


    // Printing the values of each element of the linked list
    while(int_item)
    {
        printf("Element Value: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }

    
    printf("\n");

    //Assigning to int_item again the head of the linked list
    int_item = (struct int_item*)head;

    //-------------------------------------------------------------------------------------------------------------------------------------------
    printf("Adding an element to the head of the list. The new element becomes the new head\n");

    // Adding an element to the head of the list. The new element becomes the new head of the list
    struct int_item int_item5;
    int_item5.value = 50;
    struct list_item* current_head = list_add((struct list_item**)&int_item, (struct list_item*)&int_item5);


    // Calculating the lenght of the linked list
    len = list_lenght((struct list_item*)int_item);
    printf("Number of elements: %d\n", len);

    // Printing the values of each element of the linked list
    while(int_item)
    {
        printf("Element Value: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }

    printf("\n");

    // Assigning to int_item again the head of the linked list
    int_item = (struct int_item*)current_head;

    //-------------------------------------------------------------------------------------------------------------------------------------------
    printf("Removing an element\n");

    // Removal of an element of the linked list, given its address(& + name of the int_item)

    //current_head = remove_item((struct list_item**)&int_item, (struct list_item*)&int_item5);
    current_head = remove_item((struct list_item**)&int_item, (struct list_item*)&int_item1);
    //current_head = remove_item((struct list_item**)&int_item, (struct list_item*)&int_item2);
    //current_head = remove_item((struct list_item**)&int_item, (struct list_item*)&int_item3);
    //current_head = remove_item((struct list_item**)&int_item, (struct list_item*)&int_item4);

    // Calculating the new lenght of the Linked List
    len = list_lenght((struct list_item*)int_item);
    printf("Number of elements: %d\n", len);


    // Printing the new linked list after removing an element
    while(int_item)
    {
        printf("Element Value: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }


    printf("\n");

    //-------------------------------------------------------------------------------------------------------------------------------------------
    printf("Popping the head of the list\n");

    // Assigning to int_item again the head of the linked list
    int_item = (struct int_item*)current_head;

    // Popping the head of the list
    current_head = list_pop((struct list_item**)&int_item);

    // Checking the new lenght of the Linked List
    len = list_lenght((struct list_item*)int_item);
    printf("Number of elements: %d\n", len);


    // Printing the new linked list after popping the head of the list
    while(int_item)
    {
        printf("Element Value: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }


    printf("\n");

    int_item = (struct int_item*)current_head;
    //-------------------------------------------------------------------------------------------------------------------------------------------
    printf("Reversing a list\n");

    // Printing the reversed list
    reverse_list((struct list_item**)&int_item);

    return 0;
}

