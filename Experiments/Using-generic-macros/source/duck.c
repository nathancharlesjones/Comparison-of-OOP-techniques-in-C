#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"

#define MAX_CHARS_NAME 10

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME];
} Duck_t;

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
    printf("\tHi! My name is %s.\n", thisDuck->name);
}