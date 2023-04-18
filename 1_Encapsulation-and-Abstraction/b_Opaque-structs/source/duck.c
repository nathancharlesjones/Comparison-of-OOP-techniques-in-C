#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "duck.h"

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

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

    printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && thisDuck->name);

    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck, 0, sizeof(Duck_t));
    free(thisDuck);
}