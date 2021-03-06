#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include "assert.h"
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

bool
typeIsMallard( void const * thisType )
{
    bool ret = false;

    ASSERT(thisType);

    if( *(uint32_t *)thisType == MAGIC )
    {
        while( thisType && thisType != mallardFromHeapMem && thisType != mallardFromStaticMem )
        {
            ASSERT(((Duck_Interface)thisType)->getParentInterface);
            thisType = ((Duck_Interface)thisType)->getParentInterface();
        }

        if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) ) ret = true;
    }

    return ret;
}

bool
parentIsMallard( void const * thisType )
{
    ASSERT(thisType);

    return typeIsMallard(thisType);
}

bool
objIsMallard( void * thisMallard )
{
    bool ret = false;

    ASSERT(thisMallard);

    if( ((Duck)thisMallard)->magic_number == MAGIC )
    {
        void const * thisType = *(Mallard_Interface *)thisMallard;

        if( ( thisType == mallardFromHeapMem ) || ( thisType == mallardFromStaticMem ) || parentIsMallard(thisType) ) ret = true;
    }

    return ret;
}

void
mallardInit( Mallard thisMallard, va_list * args )
{
    ASSERT(thisMallard && objIsMallard(thisMallard) && args);

    duckInit((Duck)thisMallard, args);
    
    printf("\tInitializing mallard duck with name: %s\n", duckGetName((Duck)thisMallard));

    thisMallard->myColor = va_arg(*args, featherColor);
}

static void *
mallardCreate_dynamic( Duck_Interface thisDuckInterface, va_list * args )
{
    ASSERT(thisDuckInterface && typeIsMallard(thisDuckInterface) && args);

    Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    *(Duck_Interface *)newMallard = thisDuckInterface;
    ((Duck)newMallard)->magic_number = MAGIC;

    mallardInit(newMallard, args);

    return (void *)newMallard;
}

static void *
mallardCreate_static( Duck_Interface thisDuckInterface, va_list * args )
{
    ASSERT(thisDuckInterface && typeIsMallard(thisDuckInterface) && args);

    Mallard newMallard = NULL;

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( mallardMemoryPool[i].used == false )
        {
            mallardMemoryPool[i].used = true;
            newMallard = &mallardMemoryPool[i].thisMallard;
            *(Duck_Interface *)newMallard = thisDuckInterface;
            ((Duck)newMallard)->magic_number = MAGIC;
            mallardInit(newMallard, args);
            break;
        }
    }

    return (void *)newMallard;
}

static void *
mallardGetParent_dynamic( void )
{
    return duckFromHeapMem;
}

static void *
mallardGetParent_static( void )
{
    return duckFromStaticMem;
}

void
mallardSetFeatherColor( void * _thisMallard, featherColor color )
{
    Mallard thisMallard = (Mallard)_thisMallard;
    
    ASSERT(thisMallard && objIsMallard(thisMallard));

    thisMallard->myColor = color;
}

featherColor
mallardGetFeatherColor( void * _thisMallard )
{
    Mallard thisMallard = (Mallard)_thisMallard;
    
    ASSERT(thisMallard && objIsMallard(thisMallard));
    
    return thisMallard->myColor;
}

const char *
mallardGetFeatherColorName( void * _thisMallard )
{
    Mallard thisMallard = (Mallard)_thisMallard;
    
    ASSERT(thisMallard && objIsMallard(thisMallard));
    
    return colorNames[thisMallard->myColor];
}

static void
mallardShow( Duck thisDuck )
{
    ASSERT(thisDuck && objIsMallard(thisDuck));

    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName(thisDuck), colorNames[thisMallard->myColor]);
}

void
mallardMigrate( void * _thisMallard )
{
    Mallard thisMallard = (Mallard)_thisMallard;

    ASSERT(thisMallard && objIsMallard(thisMallard));

    if ( (*((Mallard_Interface *)thisMallard))->migrate )
    {
        (*((Mallard_Interface *)thisMallard))->migrate(thisMallard);
    }
    else
    {
        printf("\t%s: I'm migrating!\n", duckGetName((Duck)thisMallard));
    }
}

void
mallardDeinit( Mallard thisMallard )
{
    ASSERT(thisMallard && objIsMallard(thisMallard));

    printf("\tDeinitializing Mallard object with name: %s\n", duckGetName((Duck)thisMallard));

    thisMallard->myColor = 0;

    duckDeinit((Duck)thisMallard);
}

static void
mallardDestroy_dynamic( void * thisMallard )
{
    ASSERT(thisMallard && objIsMallard(thisMallard));

    mallardDeinit((Mallard)thisMallard);
    free((Mallard)thisMallard);
}

static void
mallardDestroy_static( void * thisMallard )
{
    ASSERT(thisMallard && objIsMallard(thisMallard));

    for( int i = 0; i < MAX_NUM_MALLARD_OBJS; i++)
    {
        if( (Mallard)thisMallard == &mallardMemoryPool[i].thisMallard )
        {
            mallardDeinit((Mallard)thisMallard);
            memset(&mallardMemoryPool[i].thisMallard, 0, sizeof(Mallard_t));
            mallardMemoryPool[i].used = false;
            thisMallard = NULL;
            break;
        }
    }
}

const Mallard_Interface_Struct mallardDynamic = {
    .duckInterface = { .magic_number = MAGIC,
                       .getParentInterface = mallardGetParent_dynamic,
                       .create = mallardCreate_dynamic,
                       .destroy = mallardDestroy_dynamic,
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromHeapMem = (void *)&mallardDynamic;

const Mallard_Interface_Struct mallardStatic = {
    .duckInterface = { .magic_number = MAGIC,
                       .getParentInterface = mallardGetParent_static,
                       .create = mallardCreate_static,
                       .destroy = mallardDestroy_static,
                       .show = mallardShow },
    .migrate = 0
};

void * mallardFromStaticMem = (void *)&mallardStatic;