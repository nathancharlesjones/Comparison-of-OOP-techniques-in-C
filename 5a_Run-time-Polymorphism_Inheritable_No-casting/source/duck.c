#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
    bool ret = false;

    ASSERT(thisDuck);

    void * thisType = GET_TYPE_FROM_OBJ(thisDuck);

    while( thisType && thisType != Duck )
    {
        thisType = (void *)GET_PARENT_FROM_TYPE(thisType);
    }

    if( thisType == Duck ) ret = true;

    return ret;
}

void *
duckCreate( void * newDuckType, char * name, ... )
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
        if ( newDuck && newDuck->vtable && newDuck->vtable->baseInterface.init )
        {
            newDuck->vtable->baseInterface.init((void *)newDuck, newDuckType, &args);
        }
    }

    va_end(args);

    return (void *)newDuck;
}

void *
duckCreate_dynamic( void )
{
    Duck newDuck = (Duck)malloc(sizeof(Duck_t));
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

void
duckInit( void * thisDuck, void * duckInterface, va_list * args )
{
    ASSERT(thisDuck);

    Duck _thisDuck = (Duck)thisDuck;
    char * name = va_arg(args, char *);

    printf("\tInitializing duck with name: %s\n", name);

    strncpy(_thisDuck->name, name, MAX_CHARS_NAME);
    _thisDuck->vtable = (Duck_Interface)duckInterface;
}

void
duckQuack( void * thisDuck )
{
    ASSERT(thisDuck);
    //ASSERT(isDuck(thisDuck));
    
    // This should probably be an ASSERT, like above
    if( isDuck(thisDuck) )
    {
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

const Duck_Interface_Struct duckDynamic = {
    .baseclass = { NULL },
    .create = duckCreate_dynamic,
    .init = duckInit,
    .show = 0,
    .deinit = 0,
    .destroy = duckDestroy_dynamic
};

void * duckFromHeapMem = (void *)&duckDynamic;