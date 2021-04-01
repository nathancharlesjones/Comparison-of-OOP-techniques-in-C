#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "duck.r"

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

    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckShow( Duck thisDuck )
{
    printf("\tHi! My name is %s.\n", thisDuck->name);
}