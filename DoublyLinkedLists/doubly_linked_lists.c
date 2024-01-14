#include <stddef.h>
#include <stdio.h>

struct list_item
{
    struct list_item* prev;
    struct list_item* next;
    unsigned int count;
};

struct int_item
{
    struct list_item list_item;
    int value;
};

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

// Insert item_to_insert after item
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



int main(int argc, char** argv)
{
    // head of the linked list set to NULL
    struct list_item* head = NULL;

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
    unsigned int len = list_lenght((struct list_item**)&int_item);
    printf("Number of elements: %d\n", len);

    // Printing the values of each element of the linked list
    while(int_item)
    {
        printf("Element: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }

    printf("\n");


    //---------------------------------------------------------------------------------------------
    // Inserting an item after another item

    // Assigning to int_item again the head of the linked list
    int_item = (struct int_item*)head;

    // Creating new element
    struct int_item int_item5;
    int_item5.value = 500;
    

    insert_after_item((struct list_item**)&int_item, (struct list_item*)&int_item5, (struct list_item*)&int_item3);

    // Saving the new head
    head = (struct list_item*)int_item;


    len = list_lenght((struct list_item**)&int_item);
    printf("Number of elements: %d\n", len);

    

    // Printing the new linked list after removing an element
    while(int_item)
    {
        printf("Element: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }

    printf("\n");



    //---------------------------------------------------------------------------------------------
    // Inserting an item before another item

    // Assigning to int_item again the head of the linked list
    int_item = (struct int_item*)head;

    // Creating new element
    struct int_item int_item6;
    int_item6.value = 600;

    
    // Inserting int_item6 before another item, already contained in the list
    insert_before_item((struct list_item**)&int_item, (struct list_item*)&int_item6, (struct list_item*)&int_item1);
    // insert_before_item((struct list_item**)&int_item, (struct list_item*)&int_item6, (struct list_item*)&int_item2);
    // insert_before_item((struct list_item**)&int_item, (struct list_item*)&int_item6, (struct list_item*)&int_item3);
    // insert_before_item((struct list_item**)&int_item, (struct list_item*)&int_item6, (struct list_item*)&int_item4);
    // insert_before_item((struct list_item**)&int_item, (struct list_item*)&int_item6, (struct list_item*)&int_item5);

    // Saving the new head
    head = (struct list_item*)int_item;

    len = list_lenght((struct list_item**)&int_item);
    printf("Number of elements: %d\n", len);

    // Printing the new linked list after removing an element
    while(int_item)
    {
        printf("Element: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }

    printf("\n");

    //---------------------------------------------------------------------------------------------
    // Removing an item


    // Assigning to int_item again the head of the linked list
  
    int_item = (struct int_item*)head;

    // Removal of one or more elements of the linked list, given their addresses(& + name of the int_item)
    //remove_item((struct list_item**)&int_item, (struct list_item*)&int_item1);    
    //remove_item((struct list_item**)&int_item, (struct list_item*)&int_item2);    
    //remove_item((struct list_item**)&int_item, (struct list_item*)&int_item3);    
    //remove_item((struct list_item**)&int_item, (struct list_item*)&int_item4);
    //remove_item((struct list_item**)&int_item, (struct list_item*)&int_item5);
    remove_item((struct list_item**)&int_item, (struct list_item*)&int_item6);

    len = list_lenght((struct list_item**)&int_item);
    printf("Number of elements: %d\n", len);

    // Printing the new linked list after removing an element
    while(int_item)
    {
        printf("Element: %d\n", int_item->value);
        int_item = (struct int_item*)int_item->list_item.next;
    }


    return 0;
}