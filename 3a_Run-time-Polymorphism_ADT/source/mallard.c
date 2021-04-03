#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
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

Duck
mallardCreate_dynamic( void )
{
    Mallard newMallard = (Mallard)malloc(sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return (Duck)newMallard;
}

Duck
mallardCreate_static( void )
{
    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
        }
    }

    return (Duck)newMallard;
}

void
mallardInit( Duck thisDuck, va_list * args )
{
    printf("\tInitializing mallard duck with name: %s\n", thisDuck->name);

    Mallard thisMallard = (Mallard)thisDuck;
    
    thisMallard->myColor = va_arg(*args, featherColor);
}

static void
mallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
}

void
mallardDeinit( Duck thisMallard )
{
    printf("\tDeinitializing Mallard object with name: %s\n", thisMallard->name);

    ((Mallard)thisMallard)->myColor = 0;
}

void
mallardDestroy_dynamic( Duck thisMallard )
{
    free((Mallard)thisMallard);
}

void
mallardDestroy_static( Duck thisMallard )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (Mallard)thisMallard == &mallardMemoryPool[i].thisMallard )
        {
            mallardMemoryPool[i].used = false;
            thisMallard = NULL;
        }
    }
}

Duck_Interface_Struct mallardDynamic = {
    .create=mallardCreate_dynamic,
    .init=mallardInit,
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_dynamic
};

Duck_Interface mallardFromHeapMem = &mallardDynamic;

Duck_Interface_Struct mallardStatic = {
    .create=mallardCreate_static,
    .init=mallardInit,
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_static
};

Duck_Interface mallardFromStaticMem = &mallardStatic;