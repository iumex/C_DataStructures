#include "doubly_linked_lists.h"
#include <stdlib.h>
#include <stdio.h>

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