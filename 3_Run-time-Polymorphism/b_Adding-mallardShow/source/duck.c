#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "duck.h"
#include "duck_private.h"

p_Duck_t
duckNew( char * name )
{
    p_Duck_t newDuck = (p_Duck_t)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    printf("\tInitializing new duck with name: %s\n", name);
    strncpy(newDuck->name, name, MAX_CHARS_NAME);

    return newDuck;
}

void
duckQuack( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name);
    
    printf("\t%s: Quack!!\n", thisDuck->name);
}

void
duckShow( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name);

    if( thisDuck->duckShow ) thisDuck->duckShow(thisDuck);
    else printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name);

    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck, 0, sizeof(Duck_t));
    free(thisDuck);
}