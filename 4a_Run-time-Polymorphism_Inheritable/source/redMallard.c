#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"
#include "redMallard.r"

typedef struct redMallardMemoryPool_t
{
    bool used;
    redMallard_t thisRedMallard;
} redMallardMemoryPool_t;

static redMallardMemoryPool_t redMallardMemoryPool[MAX_NUM_RED_MALLARD_OBJS] = {0};

static void
redMallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a red-breasted mallard duck. My name is %s. I have %s feathers.\n", duckGetName(thisDuck), mallardGetFeatherColorName(thisMallard));
}

static void
redMallardMigrate( Mallard thisMallard )
{
    Duck thisDuck = (Duck)thisMallard;
    printf("\t%s: I'm migrating from North to South America with my fellow red-breasted mallards!\n", duckGetName(thisDuck));
}

void
redMallardDeinit( Duck thisDuck )
{
    redMallard thisRedMallard = (redMallard)thisDuck;

    printf("\tDeinitializing red mallard object with name: %s\n", duckGetName(&thisRedMallard->parentMallard.parentDuck));
    
    mallardDeinit((Duck)thisRedMallard);
}

static void
redMallardDestroy_dynamic( Duck thisDuck )
{
    free(thisDuck);
}

static void
redMallardDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_RED_MALLARD_OBJS; i++)
    {
        if( (redMallard)thisDuck == &redMallardMemoryPool[i].thisRedMallard )
        {
            redMallardMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}

redMallard_Interface_Struct redMallardDynamic = {
    .mallardInterface = { .duckInterface = { .show = redMallardShow,
                                             .deinit = redMallardDeinit,
                                             .destroy = redMallardDestroy_dynamic },
                          .migrate = redMallardMigrate }
};

redMallard_Interface redMallardFromHeapMem = &redMallardDynamic;

redMallard_Interface_Struct redMallardStatic = {
    .mallardInterface = { .duckInterface = { .show = redMallardShow,
                                             .deinit = redMallardDeinit,
                                             .destroy = redMallardDestroy_static },
                          .migrate = redMallardMigrate }
};

redMallard_Interface redMallardFromStaticMem = &redMallardStatic;

void
redMallardInit( redMallard thisRedMallard, char * name, featherColor color )
{
    mallardInit(&thisRedMallard->parentMallard, name, color);

    printf("\tInitializing red-breasted mallard with name: %s\n", name);

    // Insert red mallard initialization here
}

redMallard
redMallardCreate_dynamic( char * name, featherColor color )
{
    redMallard newRedMallard = (redMallard)malloc(sizeof(redMallard_t));
    // TODO: Check for null pointer on malloc failure

    redMallardInit(newRedMallard, name, color);
    newRedMallard->parentMallard.parentDuck.vtable = (Duck_Interface)redMallardFromHeapMem;

    return newRedMallard;
}

redMallard
redMallardCreate_static( char * name, featherColor color )
{
    redMallard newRedMallard = NULL;

    for( int i = 0; i < MAX_NUM_RED_MALLARD_OBJS; i++)
    {
        if( redMallardMemoryPool[i].used == false )
        {
            redMallardMemoryPool[i].used = true;
            newRedMallard = &redMallardMemoryPool[i].thisRedMallard;
            redMallardInit(newRedMallard, name, color);
            newRedMallard->parentMallard.parentDuck.vtable = (Duck_Interface)redMallardFromStaticMem;
            break;
        }
    }

    return newRedMallard;
}