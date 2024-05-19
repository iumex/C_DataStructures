#include "dict_string_int.h"

#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
    size_t hashmap_size = 3;
    struct dict_table* table = dict_table_init(hashmap_size);

    table = dict_insert(table, "Primo", 50);
    table = dict_insert(table, "Secondo", 100);
    table = dict_insert(table, "Terzo", 200);

    printf("\n");
   
    table = dict_insert(table, "Quarto", 300);
    table = dict_insert(table, "Quinto", 400);
    table = dict_insert(table, "Sesto", 500);

    printf("\n");
    
    find_val_by_key(table, "Terzo");
    find_val_by_key(table, "Nono");

  

    return 0;
}