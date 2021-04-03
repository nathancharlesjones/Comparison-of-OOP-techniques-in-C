#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "duck.h"
#include "duck.r"

typedef struct Duck_t
{
    void * derivedObj;
    char name[MAX_CHARS_NAME];
} Duck_t;

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

void *
duckCreate_dynamic( void )
{
    Duck newDuck = (Duck)malloc(sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return (void *)newDuck;
}

void *
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

    return (void *)newDuck;
}

void
duckInit( void * thisDuck, void * derivedObj, char * name )
{
    printf("\tInitializing duck with name: %s\n", name);

    Duck _thisDuck = (Duck)thisDuck;
    _thisDuck->derivedObj = derivedObj;
    strncpy(_thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckShow( void * thisDuck )
{
    Duck _thisDuck = (Duck)thisDuck;
    printf("\tHi! My name is %s.\n", _thisDuck->name);
}

void
duckDeinit( void * thisDuck )
{
    Duck _thisDuck = (Duck)thisDuck;

    printf("\tDeinitializing Duck object with name: %s\n", _thisDuck->name);
    
    memset(_thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
}

void
duckDestroy_dynamic( void * thisDuck )
{
    free(thisDuck);
}

void
duckDestroy_static( void * thisDuck )
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