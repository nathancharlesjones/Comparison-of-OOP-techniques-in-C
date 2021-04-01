#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"

Duck_t *
duckCreate( void )
{
    Duck_t * newDuck = (Duck_t *)malloc(sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return newDuck;
}

void
duckInit( Duck_t * thisDuck, char * name )
{
    printf("\tInitializing new duck with name: %s\n", name);

    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckShow( Duck_t * thisDuck )
{
    printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy( Duck_t * thisDuck )
{
    printf("\tDestroying Duck object with name '%s'.\n", thisDuck->name);
    memset(thisDuck, 0, sizeof(Duck_t));
    free(thisDuck);
}