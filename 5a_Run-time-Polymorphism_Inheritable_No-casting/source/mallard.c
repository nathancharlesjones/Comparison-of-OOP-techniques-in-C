#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "assert.h"
#include "duck.h"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct mallardMemoryPool_t
{
    bool used;
    Mallard_t thisMallard;
} mallardMemoryPool_t;

static mallardMemoryPool_t mallardMemoryPool[MAX_NUM_MALLARD_OBJS] = {0};

bool
typeIsMallard( void const * thisType )
{
    bool ret = false;

    while( thisType && thisType != mallardFromHeapMem && thisType != mallardFromStaticMem )
    {
        thisType = ((Duck_Interface)thisType)->getParentInterface();
    }

    if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) ) ret = true;

    return ret;
}

bool
parentIsMallard( void const * thisType )
{
    return typeIsMallard(thisType);
}

bool
objIsMallard( void * thisMallard )
{
    bool ret = false;

    ASSERT(thisMallard);

    void const * thisType = *(Mallard_Interface *)thisMallard;

    if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) || parentIsMallard(thisType) ) ret = true;

    return ret;
}

void
mallardInit( Mallard thisMallard, va_list * args )
{
    ASSERT(thisMallard);
    ASSERT(objIsMallard(thisMallard));

    duckInit((Duck)thisMallard, args);
    
    printf("\tInitializing mallard duck with name: %s\n", duckGetName((Duck)thisMallard));

    thisMallard->myColor = va_arg(*args, featherColor);
}

static void *
mallardCreate_dynamic( Duck_Interface thisDuckInterface, va_list * args )
{
    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    *(Duck_Interface *)newMallard = thisDuckInterface;

    mallardInit(newMallard, args);

    return (void *)newMallard;
}

static void *
mallardCreate_static( Duck_Interface thisDuckInterface, va_list * args )
{
    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
            *(Duck_Interface *)newMallard = thisDuckInterface;
            mallardInit(newMallard, args);
            break;
        }
    }

    return (void *)newMallard;
}

static void *
mallardGetParent_dynamic( void )
{
    return duckFromHeapMem;
}

static void *
mallardGetParent_static( void )
{
    return duckFromStaticMem;
}

void
mallardSetFeatherColor( void * thisMallard, featherColor color )
{
    ASSERT(thisMallard);
    ASSERT(objIsMallard(thisMallard));

    Mallard _thisMallard = (Mallard)thisMallard;
    _thisMallard->myColor = color;
}

featherColor
mallardGetFeatherColor( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(objIsMallard(thisMallard));
    
    Mallard _thisMallard = (Mallard)thisMallard;
    return _thisMallard->myColor;
}

const char *
mallardGetFeatherColorName( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(objIsMallard(thisMallard));
    
    Mallard _thisMallard = (Mallard)thisMallard;
    return colorNames[_thisMallard->myColor];
}

static void
mallardShow( Duck thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsMallard(thisDuck));

    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName(thisDuck), colorNames[thisMallard->myColor]);
}

void
mallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(objIsMallard(thisMallard));

    Mallard _thisMallard = (Mallard)thisMallard;

    if ( _thisMallard && *((Mallard_Interface *)_thisMallard) && (*((Mallard_Interface *)_thisMallard))->migrate )
    {
        (*((Mallard_Interface *)_thisMallard))->migrate(thisMallard);
    }
    else
    {
        printf("\t%s: I'm migrating!\n", duckGetName((Duck)_thisMallard));
    }
}

void
mallardDeinit( Mallard thisMallard )
{
    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName((Duck)thisMallard));

    thisMallard->myColor = 0;

    duckDeinit((Duck)thisMallard);
}

static void
mallardDestroy_dynamic( void * thisMallard )
{
    mallardDeinit((Mallard)thisMallard);

    free((Mallard)thisMallard);
}

static void
mallardDestroy_static( void * thisMallard )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (Mallard)thisMallard == &mallardMemoryPool[i].thisMallard )
        {
            mallardDeinit((Mallard)thisMallard);

            memset(&mallardMemoryPool[i].thisMallard, 0, sizeof(Mallard_t));
            mallardMemoryPool[i].used = false;
            thisMallard = NULL;
            break;
        }
    }
}

const Mallard_Interface_Struct mallardDynamic = {
    .duckInterface = { .getParentInterface = mallardGetParent_dynamic,
                       .create = mallardCreate_dynamic,
                       .destroy = mallardDestroy_dynamic,
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromHeapMem = (void *)&mallardDynamic;

const Mallard_Interface_Struct mallardStatic = {
    .duckInterface = { .getParentInterface = mallardGetParent_static,
                       .create = mallardCreate_static,
                       .destroy = mallardDestroy_static,
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromStaticMem = (void *)&mallardStatic;