#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "duck.h"
#include "assert.h"

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

Duck
duckCreate_dynamic( void )
{
    Duck newDuck = (Duck)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return newDuck;
}

Duck
duckCreate_static( void )
{
    Duck newDuck = NULL;

    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( duckMemoryPool[i].used == false )
        {
            duckMemoryPool[i].used = true;
            newDuck = &duckMemoryPool[i].thisDuck;
            break;
        }
    }

    return newDuck;
}

void
duckInit( Duck thisDuck, char * name )
{
    ASSERT(thisDuck);

    printf("\tInitializing new duck with name: %s\n", name);

    memset(thisDuck, 0, sizeof(Duck_t));
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckSetName( Duck thisDuck, char * name )
{
    ASSERT(thisDuck);

    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( Duck thisDuck )
{
    ASSERT(thisDuck);

    return thisDuck->name;
}

void
duckShow( Duck thisDuck )
{
    ASSERT(thisDuck);

    printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy_dynamic( Duck thisDuck )
{
    ASSERT(thisDuck);

    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck, 0, sizeof(Duck_t));
    free(thisDuck);
}

void
duckDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( thisDuck == &duckMemoryPool[i].thisDuck )
        {
            printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
            memset(&duckMemoryPool[i].thisDuck, 0, sizeof(Duck_t));
            duckMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}