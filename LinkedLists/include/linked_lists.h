#ifndef LINKED_LISTS_H
#define LINKED_LISTS_H


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
struct list_item* list_get_tail(struct list_item** head);

// Function to append a new element to the linked list
struct list_item* list_append(struct list_item** head, struct list_item* item);

// Lenght of the linked list
unsigned int list_lenght(struct list_item* head);

// Function to pop the head of the linked list
struct list_item* list_pop(struct list_item** head);

// Function to add an element to the head of the list. The added element becomes the new head
struct list_item* list_add(struct list_item** head, struct list_item* item);

// Function to remove an element of the linked list, given its address
struct list_item* remove_item(struct list_item** head, struct list_item* item);

// Function to print the reversed list
struct list_item* reverse_list(struct list_item** head);



#endif // LINKED_LISTS_H