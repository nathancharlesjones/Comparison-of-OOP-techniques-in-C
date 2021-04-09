#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "assert.h"
#include "mallard.h"
#include "redMallard.h"
#include "redMallard.r"

typedef struct redMallardMemoryPool_t
{
    bool used;
    redMallard_t thisRedMallard;
} redMallardMemoryPool_t;

static redMallardMemoryPool_t redMallardMemoryPool[MAX_NUM_RED_MALLARD_OBJS] = {0};

bool
typeIsRedMallard( void const * thisType )
{
    bool ret = false;

    while( thisType && thisType != redMallardFromHeapMem && thisType != redMallardFromStaticMem )
    {
        thisType = ((Duck_Interface)thisType)->getParentInterface();
    }

    if( ( thisType == redMallardFromHeapMem ) || ( thisType == redMallardFromStaticMem ) ) ret = true;

    return ret;
}

bool
parentIsRedMallard( void const * thisType )
{
    return typeIsRedMallard(thisType);
}

bool
objIsRedMallard( void * thisRedMallard )
{
    bool ret = false;

    ASSERT(thisRedMallard);

    void const * thisType = *(redMallard_Interface *)thisRedMallard;

    if( ( thisType == redMallardFromHeapMem ) || ( thisType == redMallardFromStaticMem ) || parentIsRedMallard(thisType) ) ret = true;

    return ret;
}

void
redMallardInit( redMallard thisRedMallard, va_list * args )
{
    ASSERT(thisRedMallard);

    mallardInit((Mallard)thisRedMallard, args);
    
    printf("\tInitializing new red-breasted mallard with name: %s\n", duckGetName(&thisRedMallard->parentMallard.parentDuck));
}

static void *
redMallardCreate_dynamic( va_list * args )
{
    redMallard newRedMallard = (redMallard)calloc(1, sizeof(redMallard_t));
    // TODO: Check for null pointer on malloc failure

    redMallardInit(newRedMallard, args);

    return (void *)newRedMallard;
}

static void *
redMallardCreate_static( va_list * args )
{
    redMallard newRedMallard = NULL;

    for( int i = 0; i < MAX_NUM_RED_MALLARD_OBJS; i++)
    {
        if( redMallardMemoryPool[i].used == false )
        {
            redMallardMemoryPool[i].used = true;
            newRedMallard = &redMallardMemoryPool[i].thisRedMallard;
            redMallardInit(newRedMallard, args);
            break;
        }
    }

    return (void *)newRedMallard;
}

static void *
redMallardGetParent_dynamic( void )
{
    return mallardFromHeapMem;
}

static void *
redMallardGetParent_static( void )
{
    return mallardFromStaticMem;
}

static void
redMallardShow( Duck thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsRedMallard(thisDuck));

    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a red-breasted mallard duck. My name is %s. I have %s feathers.\n", duckGetName((void *)(&thisMallard->parentDuck)), mallardGetFeatherColorName(thisMallard));
}

void
redMallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(objIsRedMallard(thisMallard));

    Mallard _thisMallard = (Mallard)thisMallard;
    printf("\t%s: I'm migrating from North to South America with my fellow red-breasted mallards!\n", duckGetName( (void *)(&_thisMallard->parentDuck) ) );
}

void
redMallardDeinit( redMallard thisRedMallard )
{
    printf("\tDeinitializing Red Mallard object with name: %s\n", duckGetName((void *)(&thisRedMallard->parentMallard.parentDuck)));

    // Insert redMallard deinitialization here (if attributes are added to the redMallard_t struct in the future)

    mallardDeinit((Mallard)thisRedMallard);
}

static void
redMallardDestroy_dynamic( void * thisRedMallard )
{
    redMallardDeinit((redMallard)thisRedMallard);

    free((redMallard)thisRedMallard);
}

static void
redMallardDestroy_static( void * thisRedMallard )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (redMallard)thisRedMallard == &redMallardMemoryPool[i].thisRedMallard )
        {
            redMallardDeinit((redMallard)thisRedMallard);

            memset(&redMallardMemoryPool[i].thisRedMallard, 0, sizeof(Mallard_t));
            redMallardMemoryPool[i].used = false;
            thisRedMallard = NULL;
            break;
        }
    }
}

const redMallard_Interface_Struct redMallardDynamic = {
    .mallardInterface = { .duckInterface = { .getParentInterface = redMallardGetParent_dynamic,
                                             .create = redMallardCreate_dynamic,
                                             .destroy = redMallardDestroy_dynamic,
                                             .show = redMallardShow },
                          .migrate = redMallardMigrate }
};

void * redMallardFromHeapMem = (void *)&redMallardDynamic;

const redMallard_Interface_Struct redMallardStatic = {
    .mallardInterface = { .duckInterface = { .getParentInterface = redMallardGetParent_static,
                                             .create = redMallardCreate_static,
                                             .destroy = redMallardDestroy_static,
                                             .show = redMallardShow },
                          .migrate = redMallardMigrate }
};

void * redMallardFromStaticMem = (void *)&redMallardStatic;