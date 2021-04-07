#include <stdio.h>      // For printf
#include <stdlib.h>     // For malloc, free
#include <string.h>     // For strncpy, memset
#include <stdbool.h>    // For bool data type
#include <stdarg.h>     // For variadic macros (va_list, va_start, va_end)
#include "duck.h"
#include "duck.r"

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

void
duckDeinit( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    printf("\tDeinitializing duck object with name: %s\n", thisDuck->name);
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
}

void
duckDestroy( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    if( thisDuck )
    {
        if ( thisDuck->vtable && thisDuck->vtable->deinit )
        {
            thisDuck->vtable->deinit(_thisDuck);
        }

        if ( thisDuck->vtable && thisDuck->vtable->destroy )
        {
            thisDuck->vtable->destroy(_thisDuck);
        }
    }
}

static void
duckDestroy_dynamic( void * thisDuck )
{
    free((Duck)thisDuck);
}

static void
duckDestroy_static( void * thisDuck )
{
    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( (Duck)thisDuck == &duckMemoryPool[i].thisDuck )
        {
            memset(&duckMemoryPool[i].thisDuck, 0, sizeof(Duck_t));
            duckMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}

const Duck_Interface_Struct duckDynamic = {
    .show=0,
    .deinit=duckDeinit,
    .destroy=duckDestroy_dynamic
};

Duck_Interface duckFromHeapMem = &duckDynamic;

const Duck_Interface_Struct duckStatic = {
    .show=0,
    .deinit=duckDeinit,
    .destroy=duckDestroy_static
};

Duck_Interface duckFromStaticMem = &duckStatic;

void *
duckCreate_dynamic( char * name )
{
    Duck newDuck = (Duck)malloc(sizeof(Duck_t));

    duckInit(newDuck, name);
    newDuck->vtable = duckFromHeapMem;

    return (void *)newDuck;
}

void *
duckCreate_static( char * name )
{
    Duck newDuck = NULL;

    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( duckMemoryPool[i].used == false )
        {
            duckMemoryPool[i].used = true;
            newDuck = &duckMemoryPool[i].thisDuck;
            duckInit(newDuck, name);
            newDuck->vtable = duckFromStaticMem;
            break;
        }
    }

    return (void *)newDuck;
}

void
duckInit( Duck thisDuck, char * name )
{
    printf("\tInitializing duck object with name: %s\n", name);
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckSetName( void * _thisDuck, char * name )
{
    Duck thisDuck = (Duck)_thisDuck;
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    return thisDuck->name;
}

void
duckQuack( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    printf("\t%s: Quack!\n", thisDuck->name);
}

void
duckShow( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    if ( thisDuck && thisDuck->vtable && thisDuck->vtable->show )
    {
        thisDuck->vtable->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", thisDuck->name);
    }
}