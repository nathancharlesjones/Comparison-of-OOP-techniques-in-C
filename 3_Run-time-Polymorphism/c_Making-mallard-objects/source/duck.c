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

    duckInit(newDuck, name);

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

    if( thisDuck->vtable )
    {
        ASSERT( thisDuck->vtable->show );
        thisDuck->vtable->show(thisDuck);
    }
    else printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name);

    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    if( thisDuck->vtable )
    {
        ASSERT( thisDuck->vtable->deinit && thisDuck->vtable->destroy );
        thisDuck->vtable->deinit(thisDuck);

        // Duck deinitialization
        memset(thisDuck->name, 0, MAX_CHARS_NAME);

        thisDuck->vtable->destroy(thisDuck);
    }
    else
    {
        memset(thisDuck->name, 0, MAX_CHARS_NAME);
        free(thisDuck);
    }
}