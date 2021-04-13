#include <stdio.h>     // For printf
#include <stdlib.h>    // For calloc, free
#include <string.h>    // For strncpy, memset
#include <stdbool.h>   // For bool
#include <stdarg.h>    // For variadic macros (va_list, va_start, va_arg, va_end)
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
typeIsDuck( void const * thisType )
{
    bool ret = false;

    //printf("Inside typeIsDuck\n");
    //printf("thisType: %p\tduckFromHeapMem: %p\tduckFromStaticMem: %p\n", thisType, duckFromHeapMem, duckFromStaticMem);
    while( thisType && thisType != duckFromHeapMem && thisType != duckFromStaticMem )
    {
        thisType = ((Duck_Interface)thisType)->getParentInterface();
        //printf("thisType: %p\n", thisType);
    }

    if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem ) ) ret = true;

    return ret;
}

bool
parentIsDuck( void const * thisType )
{
    return typeIsDuck(thisType);
}

bool
objIsDuck( void * thisDuck )
{
    bool ret = false;

    ASSERT(thisDuck);

    void const * thisType = *(Duck_Interface *)thisDuck;

    if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem ) || parentIsDuck(thisType) ) ret = true;

    return ret;
}

void *
duckCreate( void * newDuckType, ... )
{
    va_list args;
    va_start(args, newDuckType);

    Duck newDuck = NULL;

    ASSERT(typeIsDuck(newDuckType));
    Duck_Interface newInterface = (Duck_Interface)newDuckType;
    
    if( newInterface && newInterface->create )
    {
        newDuck = newInterface->create(newInterface, &args);
    }
    
    if( newDuck )
    {
        *(Duck_Interface *)newDuck = newInterface;
    }

    va_end(args);

    return (void *)newDuck;
}

static void *
duckCreate_dynamic( Duck_Interface thisDuckInterface, va_list * args )
{
    Duck newDuck = (Duck)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    *(Duck_Interface *)newDuck = thisDuckInterface;

    duckInit(newDuck,args);

    return (void *)newDuck;
}

static void *
duckCreate_static( Duck_Interface thisDuckInterface, va_list * args )
{
    Duck newDuck = NULL;

    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( duckMemoryPool[i].used == false )
        {
            duckMemoryPool[i].used = true;
            newDuck = &duckMemoryPool[i].thisDuck;
            *(Duck_Interface *)newDuck = thisDuckInterface;
            duckInit(newDuck, args);
            break;
        }
    }

    return (void *)newDuck;
}

void
duckInit( Duck thisDuck, va_list * args )
{
    ASSERT(thisDuck);
    ASSERT(objIsDuck(thisDuck));

    char * name = va_arg(*args, char *);
    
    printf("\tInitializing duck with name: %s\n", name);

    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

static void *
duckGetParent( void )
{
    return NULL;
}

void
duckSetName( void * thisDuck, char * name )
{
    ASSERT(thisDuck);
    ASSERT(objIsDuck(thisDuck));
    Duck _thisDuck = (Duck)thisDuck;
    strncpy(_thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( void * thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsDuck(thisDuck));
    Duck _thisDuck = (Duck)thisDuck;
    return _thisDuck->name;
}

void
duckQuack( void * thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsDuck(thisDuck));
    
    Duck _thisDuck = (Duck)thisDuck;

    printf("\t%s: Quack!\n", _thisDuck->name);
}

void
duckShow( void * thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsDuck(thisDuck));
    
    Duck _thisDuck = (Duck)thisDuck;

    if ( _thisDuck && *(Duck_Interface *)_thisDuck && (*(Duck_Interface *)_thisDuck)->show )
    {
        (*(Duck_Interface *)_thisDuck)->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", _thisDuck->name);
    }
}

void
duckDestroy( void * thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsDuck(thisDuck));
    
    Duck _thisDuck = (Duck)thisDuck;

    if ( _thisDuck && *((Duck_Interface *)_thisDuck) && (*((Duck_Interface *)_thisDuck))->destroy )
    {
        (*((Duck_Interface *)_thisDuck))->destroy(thisDuck);
    }
}

void
duckDeinit( Duck thisDuck )
{
    printf("\tDeinitializing duck object with name: %s\n", thisDuck->name);
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
}

static void
duckDestroy_dynamic( void * thisDuck )
{
    duckDeinit((Duck)thisDuck);

    free((Duck)thisDuck);
}

static void
duckDestroy_static( void * thisDuck )
{
    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( (Duck)thisDuck == &duckMemoryPool[i].thisDuck )
        {
            duckDeinit((Duck)thisDuck);

            memset(&duckMemoryPool[i].thisDuck, 0, sizeof(Duck_t));
            duckMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}

const Duck_Interface_Struct duckDynamic = {
    .getParentInterface = duckGetParent,
    .create = duckCreate_dynamic,
    .destroy = duckDestroy_dynamic,
    .show = 0
};

void * duckFromHeapMem = (void *)&duckDynamic;

const Duck_Interface_Struct duckStatic = {
    .getParentInterface = duckGetParent,
    .create = duckCreate_static,
    .destroy = duckDestroy_static,
    .show = 0
};

void * duckFromStaticMem = (void *)&duckStatic;