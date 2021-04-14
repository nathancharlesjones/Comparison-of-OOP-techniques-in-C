#include <stdio.h>      // For printf
#include <stdlib.h>     // For malloc, free
#include <string.h>     // For strncpy, memset
#include <stdbool.h>    // For bool data type
#include <stdarg.h>     // For variadic macros (va_list, va_start, va_end)
#include "assert.h"
#include "duck.h"
#include "duck.r"

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

void
duckDeinit( Duck thisDuck )
{
    ASSERT(thisDuck);
    
    printf("\tDeinitializing duck object with name: %s\n", thisDuck->name);
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
}

void
duckDestroy( Duck thisDuck )
{
    ASSERT(thisDuck && *(Duck_Interface *)thisDuck);
    
    if( (*((Duck_Interface *)thisDuck))->deinit )
    {
        (*((Duck_Interface *)thisDuck))->deinit(thisDuck);
    }

    if( (*((Duck_Interface *)thisDuck))->destroy )
    {
        (*((Duck_Interface *)thisDuck))->destroy(thisDuck);
    }
}

static void
duckDestroy_dynamic( Duck thisDuck )
{
    ASSERT(thisDuck);
    
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

Duck
duckCreate_dynamic( char * name )
{
    ASSERT(name);
    
    Duck newDuck = (Duck)calloc(1, sizeof(Duck_t));

    duckInit(newDuck, name);
    newDuck->vtable = duckFromHeapMem;

    return newDuck;
}

Duck
duckCreate_static( char * name )
{
    ASSERT(name);
    
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

    return newDuck;
}

void
duckInit( Duck thisDuck, char * name )
{
    ASSERT(thisDuck && name);
    
    printf("\tInitializing duck object with name: %s\n", name);
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
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

void
duckQuack( Duck thisDuck )
{
    ASSERT(thisDuck);
    
    printf("\t%s: Quack!\n", thisDuck->name);
}

void
duckShow( Duck thisDuck )
{
    ASSERT(thisDuck && *(Duck_Interface *)thisDuck);
    
    if( (*((Duck_Interface *)thisDuck))->show )
    {
        (*((Duck_Interface *)thisDuck))->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", thisDuck->name);
    }
}