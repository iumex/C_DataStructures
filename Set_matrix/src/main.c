#include "set_matrix.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    struct set mySet;

    memset(&mySet, 0, sizeof(struct set));

    // Insert
    set_insert(&mySet, "Ciao");
    set_insert(&mySet, "Hello");
    set_insert(&mySet, "Test");
    set_insert(&mySet, "Pippo");
    set_insert(&mySet, "Parenzo");
    set_insert(&mySet, "Topolino");
    set_insert(&mySet, "Hotel");

    printf("\n");

    // Trying to insert a key already in the set
    set_insert(&mySet, "Pippo");    
    set_insert(&mySet, "Test");
    printf("\n");

    // Trying to find a key in the set
    set_find(&mySet, "Ciao");
    set_find(&mySet, "Pluto");
    set_find(&mySet, "Test");
    printf("\n");

    // Removing a key from the set and trying to find the same key after the removal. Checking if the key after takes the place of the removed key
    set_remove(&mySet, "Hello");
    set_find(&mySet, "Hello");
    set_find(&mySet, "Parenzo");
    printf("\n");

    // Inserting the same key again and checking if it's in the set, but in a different position as before
    set_insert(&mySet, "Hello");
    set_find(&mySet, "Hello");
    printf("\n");

    // Removing the key, current head of the list, and checking if the key after becomes the new head
    set_remove(&mySet, "Ciao");
    set_find(&mySet, "Parenzo");
    set_find(&mySet, "Hello");
    printf("\n");

    // Inserting the key that was the previous head again, and checking if it is stored in the last slot
    set_insert(&mySet, "Ciao");
    set_find(&mySet, "Ciao");
    printf("\n");

    return 0;
}