#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "duck.h"
#include "duck.r"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct mallardMemoryPool_t
{
    bool used;
    Mallard_t thisMallard;
} mallardMemoryPool_t;

static mallardMemoryPool_t mallardMemoryPool[MAX_NUM_MALLARD_OBJS] = {0};

void
mallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName(&thisMallard->parentDuck), colorNames[thisMallard->myColor]);
}

void
mallardMigrate( Mallard thisMallard )
{
    if ( thisMallard && thisMallard->parentDuck.vtable && ((Mallard_Interface)(thisMallard->parentDuck.vtable))->migrate )
    {
        ((Mallard_Interface)(thisMallard->parentDuck.vtable))->migrate(thisMallard);
    }
    else
    {
        printf("\t%s: I'm migrating!\n", duckGetName(&thisMallard->parentDuck));
    }
}

void
mallardDeinit( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;

    printf("\tDeinitializing mallard object with name: %s\n", duckGetName(&thisMallard->parentDuck));
    
    thisMallard->myColor = 0;
    
    duckDeinit((Duck)thisMallard);
}

void
mallardDestroy_dynamic( Duck thisDuck )
{
    free(thisDuck);
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

const Mallard_Interface_Struct mallardDynamic = {
    .duckInterface = { .show=mallardShow,
                         .deinit=mallardDeinit,
                         .destroy=mallardDestroy_dynamic },
    .migrate = 0
};

Mallard_Interface mallardFromHeapMem = &mallardDynamic;

const Mallard_Interface_Struct mallardStatic = {
    .duckInterface = { .show=mallardShow,
                         .deinit=mallardDeinit,
                         .destroy=mallardDestroy_static },
    .migrate = 0
};

Mallard_Interface mallardFromStaticMem = &mallardStatic;

Mallard
mallardCreate_dynamic( char * name, featherColor color )
{
    Mallard newMallard = (Mallard)malloc(sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    mallardInit(newMallard, name, color);
    newMallard->parentDuck.vtable = (Duck_Interface)mallardFromHeapMem;

    return newMallard;
}

Mallard
mallardCreate_static( char * name, featherColor color )
{
    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
            mallardInit(newMallard, name, color);
            newMallard->parentDuck.vtable = (Duck_Interface)mallardFromStaticMem;
            break;
        }
    }

    return newMallard;
}

void
mallardInit( Mallard thisMallard, char * name, featherColor color )
{
    duckInit((Duck)thisMallard, name);

    printf("\tInitializing mallard duck with name: %s\n", name);

    thisMallard->myColor = color;
}

void
mallardSetFeatherColor( Mallard thisMallard, featherColor color )
{
    thisMallard->myColor = color;
}

featherColor
mallardGetFeatherColor( Mallard thisMallard )
{
    return thisMallard->myColor;
}

const char *
mallardGetFeatherColorName( Mallard thisMallard )
{
    return colorNames[thisMallard->myColor];
}