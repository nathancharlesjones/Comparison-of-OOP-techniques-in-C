#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include "duck.h"
#include "duck.r"
#include "mallard.h"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;

typedef struct mallardMemoryPool_t
{
    bool used;
    Mallard_t thisMallard;
} mallardMemoryPool_t;

static mallardMemoryPool_t mallardMemoryPool[MAX_NUM_MALLARD_OBJS] = {0};

static Duck
mallardCreate_dynamic( void )
{
    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return (Duck)newMallard;
}

static Duck
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

    return (Duck)newMallard;
}

static void
mallardInit( Duck thisDuck, va_list * args )
{
    printf("\tInitializing mallard duck with name: %s\n", duckGetName(thisDuck));

    Mallard thisMallard = (Mallard)thisDuck;
    
    thisMallard->myColor = va_arg(*args, featherColor);
}

static void
mallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName(&thisMallard->parentDuck), colorNames[thisMallard->myColor]);
}

static void
mallardDeinit( Duck thisMallard )
{
    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName(thisMallard));

    ((Mallard)thisMallard)->myColor = 0;
}

static void
mallardDestroy_dynamic( Duck thisMallard )
{
    free((Mallard)thisMallard);
}

static void
mallardDestroy_static( Duck thisMallard )
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

const Duck_Interface_Struct mallardDynamic = {
    .create=mallardCreate_dynamic,
    .init=mallardInit,
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_dynamic
};

Duck_Interface mallardFromHeapMem = &mallardDynamic;

const Duck_Interface_Struct mallardStatic = {
    .create=mallardCreate_static,
    .init=mallardInit,
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_static
};

Duck_Interface mallardFromStaticMem = &mallardStatic;