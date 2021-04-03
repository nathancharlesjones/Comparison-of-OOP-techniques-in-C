#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "duck.h"
#include "duck.r"
#include "mallard.h"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;

static void mallardShow( Duck thisDuck );

static Duck_Interface_Struct interface = {
    .show=mallardShow
};

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
mallardInit( Duck thisDuck, char * name, featherColor color )
{
    printf("\tInitializing new mallard duck with name: %s\n", name);

    duckInit( thisDuck, name );

    Mallard thisMallard = (Mallard)thisDuck;
    thisMallard->parentDuck.vtable = &interface;
    thisMallard->myColor = color;
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

    duckDeinit(thisMallard);
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