#include <stdio.h>      // For printf
#include <stdlib.h>     // For malloc, free
#include <string.h>     // For strncpy, memset
#include <stdbool.h>    // For bool data type
#include <stdarg.h>     // For variadic macros (va_list, va_start, va_end)
#include "duck.h"
#include "duck.r"
#include "assert.h"

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

Duck
duckCreate( Duck_Interface newDuckType, char * name, ... )
{
    va_list args;
    va_start(args, name);

    Duck newDuck = NULL;
    
    ASSERT(newDuckType && newDuckType->create);
    newDuck = newDuckType->create();
    
    if( newDuck )
    {
        printf("\tInitializing duck with name: %s\n", name);

        *(Duck_Interface *)newDuck = newDuckType;
        strncpy(newDuck->name, name, MAX_CHARS_NAME);

        if ( newDuck->vtable->init )
        {
            newDuck->vtable->init(newDuck, &args);
        }
    }

    va_end(args);

    return newDuck;
}

static Duck
duckCreate_dynamic( void )
{
    Duck newDuck = (Duck)calloc(1, sizeof(Duck_t));

    return newDuck;
}

static Duck
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
duckQuack( Duck thisDuck )
{
    printf("\t%s: Quack!\n", thisDuck->name);
}

void
duckShow( Duck thisDuck )
{
    ASSERT( thisDuck && thisDuck->vtable );
    if( thisDuck->vtable->show )
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
    ASSERT( thisDuck && thisDuck->vtable );
    if( thisDuck->vtable->deinit )
    {
        thisDuck->vtable->deinit(thisDuck);
    }

    printf("\tDeinitializing Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);

    ASSERT( thisDuck->vtable->destroy );
    thisDuck->vtable->destroy(thisDuck);
}

static void
duckDestroy_dynamic( Duck thisDuck )
{
    free(thisDuck);
}

static void
duckDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( thisDuck == &duckMemoryPool[i].thisDuck )
        {
            memset(&duckMemoryPool[i].thisDuck, 0, sizeof(Duck_t));
            duckMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}

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

const Duck_Interface_Struct duckDynamic = {
    .create=duckCreate_dynamic,
    .init=0,
    .show=0,
    .deinit=0,
    .destroy=duckDestroy_dynamic
};

Duck_Interface duckFromHeapMem = &duckDynamic;

const Duck_Interface_Struct duckStatic = {
    .create=duckCreate_static,
    .init=0,
    .show=0,
    .deinit=0,
    .destroy=duckDestroy_static
};

Duck_Interface duckFromStaticMem = &duckStatic;