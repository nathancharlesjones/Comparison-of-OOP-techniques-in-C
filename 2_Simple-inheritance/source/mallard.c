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
} Mallard_t;

typedef struct mallardMemoryPool_t
{
    bool used;
    Mallard_t thisMallard;
} mallardMemoryPool_t;

static mallardMemoryPool_t mallardMemoryPool[MAX_NUM_MALLARD_OBJS] = {0};

Mallard
mallardCreate_dynamic( void )
{
    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return newMallard;
}

Mallard
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

    return newMallard;
}

void
mallardInit( Mallard thisMallard, char * name, featherColor color )
{
    printf("\tInitializing new mallard duck with name: %s\n", name);

    duckInit( &thisMallard->parentDuck, name );
    thisMallard->myColor = color;
}

void
mallardShow( Mallard thisMallard )
{
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName(&thisMallard->parentDuck), colorNames[thisMallard->myColor]);
}

void
mallardDeinit( Mallard thisMallard )
{
    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName(&thisMallard->parentDuck));
    
    thisMallard->myColor = 0;
    
    duckDeinit((Duck)thisMallard);
}

void
mallardDestroy_dynamic( Mallard thisMallard )
{
    free(thisMallard);
}

void
mallardDestroy_static( Mallard thisMallard )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( thisMallard == &mallardMemoryPool[i].thisMallard )
        {
            mallardMemoryPool[i].used = false;
            memset(&mallardMemoryPool[i].thisMallard, 0, sizeof(Mallard_t));
            thisMallard = NULL;
            break;
        }
    }
}