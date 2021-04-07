#include <stdio.h>     // For printf
#include <stdlib.h>    // For calloc, free
#include <string.h>    // For strncpy, memset
#include <stdbool.h>   // For bool
#include <stdarg.h>    // For variadic macros (va_list, va_start, va_arg, va_end)
#include "oopUtils.h"
#include "assert.h"
#include "duck.h"
#include "duck.r"

typedef struct duckMemoryPool_t
{
    bool used;
    Duck_t thisDuck;
} duckMemoryPool_t;

static duckMemoryPool_t duckMemoryPool[MAX_NUM_DUCK_OBJS] = {0};

bool
isDuck( void * thisDuck )
{
    printf("Inside isDuck\n");
    bool ret = false;

    ASSERT(thisDuck);

    void * thisType = GET_TYPE_FROM_OBJ(thisDuck);

    while( thisType && ( ( thisType != duckFromHeapMem ) || ( thisType != duckFromHeapMem ) ) )
    {
        thisType = (void *)GET_PARENT_FROM_TYPE(thisType);
    }

    if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromHeapMem ) ) ret = true;

    return ret;
}

void *
duckCreate( void * newDuckType, ... )
{
    va_list args;
    va_start(args, newDuckType);

    Duck newDuck = NULL;
    Duck_Interface newInterface = (Duck_Interface)newDuckType;
    
    if( newInterface && newInterface->baseInterface.create )
    {
        newDuck = newInterface->baseInterface.create();
    }
    
    if( newDuck )
    {
        newDuck->vtable = newInterface;

        if ( newDuck && newDuck->vtable && newDuck->vtable->baseInterface.init )
        {
            newDuck->vtable->baseInterface.init((void *)newDuck, &args);
        }
    }

    va_end(args);

    return (void *)newDuck;
}

static void *
duckCreate_dynamic( void )
{
    Duck newDuck = (Duck)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return (void *)newDuck;
}

static void *
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

    return (void *)newDuck;
}

static void
duckInit( void * thisDuck, va_list * args )
{
    ASSERT(thisDuck);

    Duck _thisDuck = (Duck)thisDuck;
    char * name = va_arg(*args, char *);
    
    printf("\tInitializing duck with name: %s\n", name);

    strncpy(_thisDuck->name, name, MAX_CHARS_NAME);
}

static void *
duckGetParent( void )
{
    return NULL;
}

void
duckSetName( void * thisDuck, char * name )
{
    Duck _thisDuck = (Duck)thisDuck;
    strncpy(_thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( void * thisDuck )
{
    Duck _thisDuck = (Duck)thisDuck;
    return _thisDuck->name;
}

void
duckQuack( void * thisDuck )
{
    printf("Inside duckQuack\n");
    ASSERT(thisDuck);
    //ASSERT(isDuck(thisDuck));
    
    // This should probably be an ASSERT, like above
    if( isDuck(thisDuck) )
    {
        printf("Inside if stmt\n");
        Duck _thisDuck = (Duck)thisDuck;

        printf("\t%s: Quack!\n", _thisDuck->name);
    }
}

void
duckShow( void * thisDuck )
{
    ASSERT(thisDuck);
    //ASSERT(isDuck(thisDuck));
    
    // This should probably be an ASSERT, like above
    if( isDuck(thisDuck) )
    {    
        Duck _thisDuck = (Duck)thisDuck;

        if ( _thisDuck && _thisDuck->vtable && _thisDuck->vtable->show )
        {
            _thisDuck->vtable->show(thisDuck);
        }
        else
        {
            printf("\tHi! My name is %s.\n", _thisDuck->name);
        }
    }
}

static void
duckDeinit( void * thisDuck )
{
    Duck _thisDuck = (Duck)thisDuck;
    printf("\tDeinitializing duck object with name: %s\n", _thisDuck->name);
    memset(_thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
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
    .baseInterface = { .getParentInterface = duckGetParent,
                       .create = duckCreate_dynamic,
                       .init = duckInit,
                       .deinit = duckDeinit,
                       .destroy = duckDestroy_dynamic },
    .show = 0
};

void * duckFromHeapMem = (void *)&duckDynamic;

const Duck_Interface_Struct duckStatic = {
    .baseInterface = { .getParentInterface = duckGetParent,
                       .create = duckCreate_static,
                       .init = duckInit,
                       .deinit = duckDeinit,
                       .destroy = duckDestroy_static },
    .show = 0
};

void * duckFromStaticMem = (void *)&duckStatic;