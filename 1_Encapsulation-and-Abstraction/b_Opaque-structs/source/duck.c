#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

p_Duck_t
duckCreate( void )
{
    p_Duck_t newDuck = (p_Duck_t)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return newDuck;
}

void
duckInit( p_Duck_t thisDuck, char * name )
{
    printf("\tInitializing new duck with name: %s\n", name);

    memset(thisDuck, 0, sizeof(Duck_t));
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckShow( p_Duck_t thisDuck )
{
    printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy( p_Duck_t thisDuck )
{
    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck, 0, sizeof(Duck_t));
    free(thisDuck);
}