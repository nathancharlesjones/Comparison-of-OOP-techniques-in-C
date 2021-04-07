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
isMallard( void * thisMallard )
{
    bool ret = false;

    ASSERT(thisMallard);

    void * thisType = GET_TYPE_FROM_OBJ(thisMallard);

    while( thisType && ( ( thisType != mallardFromHeapMem ) || ( thisType != mallardFromStaticMem ) ) )
    {
        thisType = (void *)GET_PARENT_FROM_TYPE(thisType);
    }

    if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) ) ret = true;

    return ret;
}

void *
mallardCreate_dynamic( void )
{
    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return (void *)newMallard;
}

static void *
mallardCreate_static( void )
{
    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
            break;
        }
    }

    return (void *)newMallard;
}

void
mallardInit( void * thisMallard, va_list * args )
{
    printf("Inside mallardInit\n");
    ASSERT(thisMallard);

    Mallard _thisMallard = (Mallard)thisMallard;
    *_thisMallard = (Mallard_t)duckFromHeapMem;

    //GET_PARENT_FROM_OBJ(_thisMallard)->init(thisMallard, args);
    
    printf("\tInitializing new mallard duck with name: %s\n", duckGetName(&_thisMallard->parentDuck));

    featherColor color = va_arg(*args, featherColor);
    _thisMallard->myColor = color;
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
    ASSERT(isMallard(thisDuck));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( isMallard(thisDuck) )
    {
        Mallard thisMallard = (Mallard)thisDuck;
        printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName((void *)(&thisMallard->parentDuck)), colorNames[thisMallard->myColor]);
    }
}

void
mallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(isMallard(thisMallard));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( isMallard(thisMallard) )
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

static void
mallardDeinit( void * thisMallard )
{
    Mallard _thisMallard = (Mallard)thisMallard;
    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName((void *)(&_thisMallard->parentDuck)));

    _thisMallard->myColor = 0;
}

static void
mallardDestroy_dynamic( void * thisMallard )
{
    free((Mallard)thisMallard);
}

static void
mallardDestroy_static( void * thisMallard )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (Mallard)thisMallard == &mallardMemoryPool[i].thisMallard )
        {
            memset(&mallardMemoryPool[i].thisMallard, 0, sizeof(Mallard_t));
            mallardMemoryPool[i].used = false;
            thisMallard = NULL;
            break;
        }
    }
}

const Mallard_Interface_Struct mallardDynamic = {
    .duckInterface = { .baseInterface = { .baseClass = NULL,
                                          .create = mallardCreate_dynamic,
                                          .init = mallardInit,
                                          .deinit = mallardDeinit,
                                          .destroy = mallardDestroy_dynamic },
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromHeapMem = (void *)&mallardDynamic;

const Mallard_Interface_Struct mallardStatic = {
    .duckInterface = { .baseInterface = { .baseClass = NULL,
                                          .create = mallardCreate_static,
                                          .init = mallardInit,
                                          .deinit = mallardDeinit,
                                          .destroy = mallardDestroy_static },
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromStaticMem = (void *)&mallardStatic;