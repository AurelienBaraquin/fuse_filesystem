#include <stdio.h>

//* PATH TO STORE DIR __________________________________________________________*/
char *store_dir = NULL;

void set_store_dir(char *dir)
{
    store_dir = dir;
}

char *get_store_dir(void)
{
    return store_dir;
}
