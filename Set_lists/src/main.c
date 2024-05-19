#include "set_lists.h"

#include <stdlib.h>
#include <stdio.h>


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