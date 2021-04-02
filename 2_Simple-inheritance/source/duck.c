#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "duck.h"
#include "duck.r"

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

Duck
duckCreate_dynamic( void )
{
    Duck newDuck = (Duck)malloc(sizeof(Duck_t));
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
        }
    }

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

void
duckDeinit( Duck thisDuck )
{
    printf("\tDeinitializing Duck object with name: %s\n", thisDuck->name);
    
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
}

void
duckDestroy_dynamic( Duck thisDuck )
{
    free(thisDuck);
}

void
duckDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( thisDuck == &duckMemoryPool[i].thisDuck )
        {
            duckMemoryPool[i].used = false;
            thisDuck = NULL;
        }
    }
}