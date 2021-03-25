#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "duck.r"

static void _duckShow( Duck thisDuck );

static Duck_Interface_Struct interface = {
    _duckShow
};

Duck
duckCreate( void )
{
    Duck newDuck = (Duck)malloc(sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return newDuck;
}

void
duckInit( Duck thisDuck, char * name )
{
    printf("\tInitializing duck with name: %s\n", name);

    thisDuck->vtable = &interface;
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
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
}

static void
_duckShow( Duck thisDuck )
{
    printf("\tHi! My name is %s.\n", thisDuck->name);
}