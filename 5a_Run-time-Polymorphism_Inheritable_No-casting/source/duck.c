#include <stdio.h>     // For printf
#include <stdlib.h>    // For calloc, free
#include <string.h>    // For strncpy, memset
#include <stdbool.h>   // For bool
#include <stdarg.h>    // For variadic macros (va_list, va_start, va_arg, va_end)
#include <stdint.h>    // For uint32_t
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

    ASSERT(thisType);

    if( *(uint32_t *)thisType == MAGIC )
    {
        while( thisType && thisType != duckFromHeapMem && thisType != duckFromStaticMem )
        {
            ASSERT(((Duck_Interface)thisType)->getParentInterface);
            thisType = ((Duck_Interface)thisType)->getParentInterface();
        }

        if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem ) ) ret = true;
    }

    return ret;
}

bool
parentIsDuck( void const * thisType )
{
    ASSERT(thisType);

    return typeIsDuck(thisType);
}

bool
objIsDuck( void * thisDuck )
{
    bool ret = false;

    ASSERT(thisDuck);

    if( ((Duck)thisDuck)->magic_number == MAGIC )
    {
        void const * thisType = *(Duck_Interface *)thisDuck;

        if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem ) || parentIsDuck(thisType) ) ret = true;
    }

    return ret;
}

void *
duckCreate( void * newDuckType, ... )
{
    va_list args;
    va_start(args, newDuckType);

    ASSERT(newDuckType && typeIsDuck(newDuckType));
    Duck newDuck = NULL;
    Duck_Interface newInterface = (Duck_Interface)newDuckType;

    ASSERT(newInterface->create);
    newDuck = newInterface->create(newInterface, &args);
    
    va_end(args);

    return (void *)newDuck;
}

static void *
duckCreate_dynamic( Duck_Interface thisDuckInterface, va_list * args )
{
    ASSERT(thisDuckInterface && args);
    
    Duck newDuck = (Duck)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    *(Duck_Interface *)newDuck = thisDuckInterface;
    newDuck->magic_number = MAGIC;

    duckInit(newDuck,args);

    return (void *)newDuck;
}

static void *
duckCreate_static( Duck_Interface thisDuckInterface, va_list * args )
{
    ASSERT(thisDuckInterface && args);
    
    Duck newDuck = NULL;

    for( int i = 0; i < MAX_NUM_DUCK_OBJS; i++)
    {
        if( duckMemoryPool[i].used == false )
        {
            duckMemoryPool[i].used = true;
            newDuck = &duckMemoryPool[i].thisDuck;
            *(Duck_Interface *)newDuck = thisDuckInterface;
            newDuck->magic_number = MAGIC;
            duckInit(newDuck, args);
            break;
        }
    }

    return (void *)newDuck;
}

void
duckInit( Duck thisDuck, va_list * args )
{
    ASSERT(thisDuck && objIsDuck(thisDuck) && args);

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
duckSetName( void * _thisDuck, char * name )
{
    Duck thisDuck = (Duck)_thisDuck;
    
    ASSERT(thisDuck && objIsDuck(thisDuck) && name);

    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

char *
duckGetName( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    
    ASSERT(thisDuck && objIsDuck(thisDuck));

    return thisDuck->name;
}

void
duckQuack( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;

    ASSERT(thisDuck && objIsDuck(thisDuck));
    
    printf("\t%s: Quack!\n", thisDuck->name);
}

void
duckShow( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;

    ASSERT(thisDuck && objIsDuck(thisDuck));
    
    if ( (*(Duck_Interface *)thisDuck)->show )
    {
        (*(Duck_Interface *)thisDuck)->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", thisDuck->name);
    }
}

void
duckDestroy( void * _thisDuck )
{
    Duck thisDuck = (Duck)_thisDuck;
    
    ASSERT(thisDuck && objIsDuck(thisDuck));
    
    ASSERT( (*((Duck_Interface *)_thisDuck))->destroy );
    (*((Duck_Interface *)_thisDuck))->destroy(thisDuck);
}

void
duckDeinit( Duck thisDuck )
{
    ASSERT(thisDuck && objIsDuck(thisDuck));

    printf("\tDeinitializing duck object with name: %s\n", thisDuck->name);
    memset(thisDuck->name, 0, sizeof(char)*MAX_CHARS_NAME);
}

static void
duckDestroy_dynamic( void * thisDuck )
{
    ASSERT(thisDuck && objIsDuck(thisDuck));

    duckDeinit((Duck)thisDuck);
    free((Duck)thisDuck);
}

static void
duckDestroy_static( void * thisDuck )
{
    ASSERT(thisDuck && objIsDuck(thisDuck));

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
    .magic_number = MAGIC,
    .getParentInterface = duckGetParent,
    .create = duckCreate_dynamic,
    .destroy = duckDestroy_dynamic,
    .show = 0
};

void * duckFromHeapMem = (void *)&duckDynamic;

const Duck_Interface_Struct duckStatic = {
    .magic_number = MAGIC,
    .getParentInterface = duckGetParent,
    .create = duckCreate_static,
    .destroy = duckDestroy_static,
    .show = 0
};

void * duckFromStaticMem = (void *)&duckStatic;