#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"

char duck_name[MAX_CHARS_NAME_WITH_NUL] = {0};

void
duckInit( char * name )
{
    // Optional: Add check to see if Singleton has already been
    // initialized.
    
    printf("\tInitializing new duck with name: %s\n", name);
    strncpy(duck_name, name, MAX_CHARS_NAME);
}

void
duckShow( void )
{
    printf("\tHi! My name is %s.\n", duck_name);
}
