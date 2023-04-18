#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "duck.h"
#include "duck_private.h"

void
duckQuack( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name);
    
    printf("\t%s: Quack!!\n", thisDuck->name);
}

void
duckShow( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name && thisDuck->vtable && thisDuck->vtable->show);

    thisDuck->vtable->show(thisDuck);
}

void
duckDestroy( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name && thisDuck->vtable);
    ASSERT(thisDuck->vtable->deinit && thisDuck->vtable->destroy);

    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    
    thisDuck->vtable->deinit(thisDuck);
    
    // Duck deinitialization
    memset(thisDuck->name, 0, MAX_CHARS_NAME);

    thisDuck->vtable->destroy(thisDuck);
}