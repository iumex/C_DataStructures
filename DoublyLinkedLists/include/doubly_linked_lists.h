#ifndef DOUBLY_LINKED_LISTS_H
#define DOUBLY_LINKED_LISTS_H

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

// Function to get the tail of the doubly linked list
struct list_item* list_get_tail(struct list_item** head);

// Function to append a new element to the doubly linked list
struct list_item* list_append(struct list_item** head, struct list_item* item);

// Lenght of the doubly linked list
unsigned int list_lenght(struct list_item** head);

// Function to remove an item
struct list_item* remove_item(struct list_item** head, struct list_item* item);

// Insert item_to_insert after item
struct list_item* insert_after_item(struct list_item** head, struct list_item* item_to_insert, struct list_item* item);

// Insert item_to_insert before item
struct list_item* insert_before_item(struct list_item** head, struct list_item* item_to_insert, struct list_item* item);



#endif //DOUBLY_LINKED_LISTS_H