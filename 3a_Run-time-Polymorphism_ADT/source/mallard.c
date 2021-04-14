#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "assert.h"
#include "duck.h"
#include "duck.r"
#include "mallard.h"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct Mallard_t
{
    const Duck_t parentDuck;
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

static void
mallardInit( Mallard thisMallard, Duck_Interface interface, char * name, featherColor color )
{
    ASSERT(thisMallard && interface && name);
    
    printf("\tInitializing new mallard duck with name: %s\n", name);

    duckSetName((Duck)thisMallard, name);
    *(Duck_Interface *)thisMallard = interface;
    thisMallard->myColor = color;
}

Duck
mallardCreate_dynamic( char * name, featherColor color )
{
    ASSERT(name);
    
    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    mallardInit(newMallard, &interface_dynamic, name, color);

    return (Duck)newMallard;
}

Duck
mallardCreate_static( char * name, featherColor color )
{
    ASSERT(name);
    
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
    ASSERT(thisDuck);
    
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName((Duck)thisMallard), colorNames[thisMallard->myColor]);
}

static void
mallardDeinit( Duck thisDuck )
{
    ASSERT(thisDuck);
    
    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName(thisDuck));

    ((Mallard)thisDuck)->myColor = 0;
}

static void
mallardDestroy_dynamic( Duck thisDuck )
{
    ASSERT(thisDuck);
    
    free((Mallard)thisDuck);
}

static void
mallardDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (Mallard)thisDuck == &mallardMemoryPool[i].thisMallard )
        {
            mallardMemoryPool[i].used = false;
            memset(&mallardMemoryPool[i].thisMallard, 0, sizeof(Mallard_t));
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