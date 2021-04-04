#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "duck.r"

void
duckSetName( Duck thisDuck, char * name )
{
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( Duck thisDuck )
{
    return thisDuck->name;
}

void
duckQuack( Duck thisDuck )
{
    printf("\t%s: Quack!\n", thisDuck->name);
}

void
duckShow( Duck thisDuck )
{
    if ( thisDuck && thisDuck->vtable && thisDuck->vtable->show )
    {
        thisDuck->vtable->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", thisDuck->name);
    }
}

void
duckDestroy( Duck thisDuck )
{
    if( thisDuck )
    {
        if ( thisDuck->vtable && thisDuck->vtable->deinit )
        {
            thisDuck->vtable->deinit(thisDuck);
        }

        printf("\tDeinitializing Duck object with name: %s\n", thisDuck->name);
        memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);

        if ( thisDuck->vtable && thisDuck->vtable->destroy )
        {
            thisDuck->vtable->destroy(thisDuck);
        }
    }
}