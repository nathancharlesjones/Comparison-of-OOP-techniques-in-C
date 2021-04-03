#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "duck.h"
#include "duck.r"
#include "rubber.h"

const char * sizeNames[] = {"small", "medium", "large"};

typedef struct Rubber_t
{
    Duck_t parentDuck;
    duck_size size;
} Rubber_t, *Rubber;

typedef struct rubberMemoryPool_t
{
    bool used;
    Rubber_t thisRubber;
} rubberMemoryPool_t;

static rubberMemoryPool_t rubberMemoryPool[MAX_NUM_RUBBER_OBJS] = {0};

static const Duck_Interface_Struct interface_dynamic;
static const Duck_Interface_Struct interface_static;

void
rubberInit( Rubber thisRubber, Duck_Interface interface, char * name, duck_size size )
{
    printf("\tInitializing new rubber duck with name: %s\n", name);

    strncpy(thisRubber->parentDuck.name, name, MAX_CHARS_NAME);
    thisRubber->parentDuck.vtable = interface;
    thisRubber->size = size;
}

Duck
rubberCreate_dynamic( char * name, duck_size size )
{
    Rubber newRubber = (Rubber)malloc(sizeof(Rubber_t));
    // TODO: Check for null pointer on malloc failure

    rubberInit(newRubber, &interface_dynamic, name, size);

    return (Duck)newRubber;
}

Duck
rubberCreate_static( char * name, duck_size size )
{
    Rubber newRubber = NULL;

    for( int i = 0; i < MAX_NUM_RUBBER_OBJS; i++)
    {
        if( rubberMemoryPool[i].used == false )
        {
            rubberMemoryPool[i].used = true;
            newRubber = &rubberMemoryPool[i].thisRubber;
            rubberInit(newRubber, &interface_static, name, size);
            break;
        }
    }

    return (Duck)newRubber;
}

static void
rubberShow( Duck thisDuck )
{
    Rubber thisRubber = (Rubber)thisDuck;
    printf("\tHi! I'm a %s rubber duck. My name is %s.\n", sizeNames[thisRubber->size], thisRubber->parentDuck.name);
}

static void
rubberDeinit( Duck thisDuck )
{
    printf("\tDeinitializing Rubber Duck object with name: %s\n", thisDuck->name);

    ((Rubber)thisDuck)->size = 0;
}

void
rubberDestroy_dynamic( Duck thisDuck )
{
    free((Rubber)thisDuck);
}

void
rubberDestroy_static( Duck thisDuck )
{
    for( int i = 0; i < MAX_NUM_RUBBER_OBJS; i++)
    {
        if( (Rubber)thisDuck == &rubberMemoryPool[i].thisRubber )
        {
            rubberMemoryPool[i].used = false;
            thisDuck = NULL;
            break;
        }
    }
}

static const Duck_Interface_Struct interface_dynamic = {
    .show=rubberShow,
    .deinit=rubberDeinit,
    .destroy=rubberDestroy_dynamic
};

static const Duck_Interface_Struct interface_static = {
    .show=rubberShow,
    .deinit=rubberDeinit,
    .destroy=rubberDestroy_static
};