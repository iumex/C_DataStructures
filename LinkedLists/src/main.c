#include "linked_lists.h"
#include <stdlib.h>
#include <stdio.h>


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