#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
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

    ASSERT(thisType);

    if( *(uint32_t *)thisType == MAGIC )
    {
        while( thisType && thisType != redMallardFromHeapMem && thisType != redMallardFromStaticMem )
        {
            ASSERT(((Duck_Interface)thisType)->getParentInterface);
            thisType = ((Duck_Interface)thisType)->getParentInterface();
        }

        if( ( thisType == redMallardFromHeapMem ) || ( thisType == redMallardFromStaticMem ) ) ret = true;
    }

    return ret;
}

bool
parentIsRedMallard( void const * thisType )
{
    ASSERT(thisType);

    return typeIsRedMallard(thisType);
}

bool
objIsRedMallard( void * thisRedMallard )
{
    bool ret = false;

    ASSERT(thisRedMallard);

    if( ((Duck)thisRedMallard)->magic_number == MAGIC )
    {
        void const * thisType = *(redMallard_Interface *)thisRedMallard;

        if( ( thisType == redMallardFromHeapMem ) || ( thisType == redMallardFromStaticMem ) || parentIsRedMallard(thisType) ) ret = true;
    }

    return ret;
}

void
redMallardInit( redMallard thisRedMallard, va_list * args )
{
    ASSERT(thisRedMallard && objIsRedMallard(thisRedMallard) && args);

    mallardInit((Mallard)thisRedMallard, args);
    
    printf("\tInitializing red-breasted mallard with name: %s\n", duckGetName((Duck)thisRedMallard));

    // Insert redMallard initialization code here (if needed later)
}

static void *
redMallardCreate_dynamic( Duck_Interface thisDuckInterface, va_list * args )
{
    ASSERT(thisDuckInterface && typeIsRedMallard(thisDuckInterface) && args);

    redMallard newRedMallard = (redMallard)calloc(1, sizeof(redMallard_t));
    // TODO: Check for null pointer on malloc failure

    *(Duck_Interface *)newRedMallard = thisDuckInterface;
    ((Duck)newRedMallard)->magic_number = MAGIC;

    redMallardInit(newRedMallard, args);

    return (void *)newRedMallard;
}

static void *
redMallardCreate_static( Duck_Interface thisDuckInterface, va_list * args )
{
    ASSERT(thisDuckInterface && typeIsRedMallard(thisDuckInterface) && args);

    redMallard newRedMallard = NULL;

    for( int i = 0; i < MAX_NUM_RED_MALLARD_OBJS; i++)
    {
        if( redMallardMemoryPool[i].used == false )
        {
            redMallardMemoryPool[i].used = true;
            newRedMallard = &redMallardMemoryPool[i].thisRedMallard;
            *(Duck_Interface *)newRedMallard = thisDuckInterface;
            ((Duck)newRedMallard)->magic_number = MAGIC;
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
    ASSERT(thisDuck && objIsRedMallard(thisDuck));

    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a red-breasted mallard duck. My name is %s. I have %s feathers.\n", duckGetName((Duck)thisMallard), mallardGetFeatherColorName(thisMallard));
}

void
redMallardMigrate( void * _thisMallard )
{
    Mallard thisMallard = (Mallard)_thisMallard;
    
    ASSERT(thisMallard && objIsRedMallard(thisMallard));

    printf("\t%s: I'm migrating from North to South America with my fellow red-breasted mallards!\n", duckGetName((Duck)thisMallard));
}

void
redMallardDeinit( redMallard thisRedMallard )
{
    ASSERT(thisRedMallard && objIsRedMallard(thisRedMallard));

    printf("\tDeinitializing Red Mallard object with name: %s\n", duckGetName((Duck)thisRedMallard));

    // Insert redMallard deinitialization here (if attributes are added to the redMallard_t struct in the future)

    mallardDeinit((Mallard)thisRedMallard);
}

static void
redMallardDestroy_dynamic( void * thisRedMallard )
{
    ASSERT(thisRedMallard && objIsRedMallard(thisRedMallard));

    redMallardDeinit((redMallard)thisRedMallard);
    free((redMallard)thisRedMallard);
}

static void
redMallardDestroy_static( void * thisRedMallard )
{
    ASSERT(thisRedMallard && objIsRedMallard(thisRedMallard));

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
    .mallardInterface = { .duckInterface = { .magic_number = MAGIC,
                                             .getParentInterface = redMallardGetParent_dynamic,
                                             .create = redMallardCreate_dynamic,
                                             .destroy = redMallardDestroy_dynamic,
                                             .show = redMallardShow },
                          .migrate = redMallardMigrate }
};

void * redMallardFromHeapMem = (void *)&redMallardDynamic;

const redMallard_Interface_Struct redMallardStatic = {
    .mallardInterface = { .duckInterface = { .magic_number = MAGIC,
                                             .getParentInterface = redMallardGetParent_static,
                                             .create = redMallardCreate_static,
                                             .destroy = redMallardDestroy_static,
                                             .show = redMallardShow },
                          .migrate = redMallardMigrate }
};

void * redMallardFromStaticMem = (void *)&redMallardStatic;