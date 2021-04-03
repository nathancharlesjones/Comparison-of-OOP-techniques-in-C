#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "duck.h"
#include "duck.r"
#include "mallard.h"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t, *Mallard;

typedef struct mallardMemoryPool_t
{
    bool used;
    Mallard_t thisMallard;
} mallardMemoryPool_t;

static mallardMemoryPool_t mallardMemoryPool[MAX_NUM_MALLARD_OBJS] = {0};

static const Duck_Interface_Struct interface_dynamic;
static const Duck_Interface_Struct interface_static;

void
mallardInit( Mallard thisMallard, Duck_Interface interface, char * name, featherColor color )
{
    printf("\tInitializing new mallard duck with name: %s\n", name);

    strncpy(thisMallard->parentDuck.name, name, MAX_CHARS_NAME);
    thisMallard->parentDuck.vtable = interface;
    thisMallard->myColor = color;
}

Duck
mallardCreate_dynamic( char * name, featherColor color )
{
    Mallard newMallard = (Mallard)malloc(sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    mallardInit( newMallard, &interface_dynamic, name, color);

    return (Duck)newMallard;
}

Duck
mallardCreate_static( char * name, featherColor color )
{
    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
            mallardInit( newMallard, &interface_static, name, color);
            break;
        }
    }

    return (Duck)newMallard;
}

static void
mallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
}

static void
mallardDeinit( Duck thisDuck )
{
    printf("\tDeinitializing Mallard object with name: %s\n", thisDuck->name);

    ((Mallard)thisDuck)->myColor = 0;
}

void
mallardDestroy_dynamic( Duck thisDuck )
{
    free((Mallard)thisDuck);
}

void
mallardDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (Mallard)thisDuck == &mallardMemoryPool[i].thisMallard )
        {
            mallardMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}

static const Duck_Interface_Struct interface_dynamic = {
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_dynamic
};

static const Duck_Interface_Struct interface_static = {
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_static
};