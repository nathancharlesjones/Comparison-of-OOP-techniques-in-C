#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

Mallard
mallardCreate_dynamic( void )
{
    Mallard newMallard = (Mallard)malloc(sizeof(Mallard_t));
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
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
}

void
mallardDestroy_dynamic( Mallard thisMallard )
{
    printf("\tDestroying Mallard object with name: %s\n", thisMallard->parentDuck.name);
    memset(thisMallard, 0, sizeof(Mallard_t));
    free(thisMallard);
}

void
mallardDestroy_static( Mallard thisMallard )
{
    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( thisMallard == &mallardMemoryPool[i].thisMallard )
        {
            printf("\tDestroying Mallard object with name: %s\n", thisMallard->parentDuck.name);
            memset(&mallardMemoryPool[i].thisMallard, 0, sizeof(Mallard_t));
            mallardMemoryPool[i].used = false;
            thisMallard = NULL;
        }
    }
}