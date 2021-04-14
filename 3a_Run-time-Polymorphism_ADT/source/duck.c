#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "duck.h"
#include "duck.r"

void
duckSetName( Duck thisDuck, char * name )
{
    ASSERT(thisDuck && name);
    
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( Duck thisDuck )
{
    ASSERT(thisDuck);
    
    return thisDuck->name;
}

void
duckQuack( Duck thisDuck )
{
    ASSERT(thisDuck);
    
    printf("\t%s: Quack!\n", thisDuck->name);
}

void
duckShow( Duck thisDuck )
{
    ASSERT(thisDuck && *(Duck_Interface *)thisDuck);
    
    if( (*((Duck_Interface *)thisDuck))->show )
    {
        (*((Duck_Interface *)thisDuck))->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", thisDuck->name);
    }
}

void
duckDestroy( Duck thisDuck )
{
    ASSERT(thisDuck && *(Duck_Interface *)thisDuck);
    
    if( (*((Duck_Interface *)thisDuck))->deinit )
    {
        (*((Duck_Interface *)thisDuck))->deinit(thisDuck);
    }

    printf("\tDeinitializing Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);

    if( (*((Duck_Interface *)thisDuck))->destroy )
    {
        (*((Duck_Interface *)thisDuck))->destroy(thisDuck);
    }
}