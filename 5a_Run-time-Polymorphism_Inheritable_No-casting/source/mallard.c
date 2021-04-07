#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include "assert.h"
#include "oopUtils.h"
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
typeIsMallard( void * thisType )
{
    bool ret = false;

    while( thisType && thisType != mallardFromHeapMem && thisType != mallardFromStaticMem )
    {
        thisType = ((BaseClass_Interface)thisType)->getParentInterface();
    }

    if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) ) ret = true;

    return ret;
}

bool
parentIsMallard( void * thisType )
{
    return typeIsMallard(thisType);
}

bool
objIsMallard( void * thisMallard )
{
    bool ret = false;

    ASSERT(thisMallard);

    void * thisType = *(BaseClass_Interface *)thisMallard;

    if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) || parentIsMallard(thisType) ) ret = true;

    return ret;
}

void
mallardInit( Mallard thisMallard, va_list * args )
{
    ASSERT(thisMallard);

    duckInit((Duck)thisMallard, args);
    
    printf("\tInitializing new mallard duck with name: %s\n", duckGetName(&thisMallard->parentDuck));

    thisMallard->myColor = va_arg(*args, featherColor);
}

static void *
mallardCreate_dynamic( va_list * args )
{
    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    mallardInit(newMallard, args);

    return (void *)newMallard;
}

static void *
mallardCreate_static( va_list * args )
{
    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
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
    Mallard _thisMallard = (Mallard)thisMallard;
    _thisMallard->myColor = color;
}

featherColor
mallardGetFeatherColor( void * thisMallard )
{
    Mallard _thisMallard = (Mallard)thisMallard;
    return _thisMallard->myColor;
}

const char *
mallardGetFeatherColorName( void * thisMallard )
{
    Mallard _thisMallard = (Mallard)thisMallard;
    return colorNames[_thisMallard->myColor];
}

static void
mallardShow( Duck thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(objIsMallard(thisDuck));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( objIsMallard(thisDuck) )
    {
        Mallard thisMallard = (Mallard)thisDuck;
        printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName((void *)(&thisMallard->parentDuck)), colorNames[thisMallard->myColor]);
    }
}

void
mallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(objIsMallard(thisMallard));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( objIsMallard(thisMallard) )
    {
        Mallard _thisMallard = (Mallard)thisMallard;

        if ( _thisMallard && _thisMallard->parentDuck.vtable && ((Mallard_Interface)(_thisMallard->parentDuck.vtable))->migrate )
        {
            ((Mallard_Interface)(_thisMallard->parentDuck.vtable))->migrate(thisMallard);
        }
        else
        {
            printf("\t%s: I'm migrating!\n", duckGetName( (void *)(&_thisMallard->parentDuck) ) );
        }
    }
}

void
mallardDeinit( Mallard thisMallard )
{
    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName((void *)(&thisMallard->parentDuck)));

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
    .duckInterface = { .baseInterface = { .getParentInterface = mallardGetParent_dynamic,
                                          .create = mallardCreate_dynamic,
                                          .destroy = mallardDestroy_dynamic },
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromHeapMem = (void *)&mallardDynamic;

const Mallard_Interface_Struct mallardStatic = {
    .duckInterface = { .baseInterface = { .getParentInterface = mallardGetParent_static,
                                          .create = mallardCreate_static,
                                          .destroy = mallardDestroy_static },
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromStaticMem = (void *)&mallardStatic;