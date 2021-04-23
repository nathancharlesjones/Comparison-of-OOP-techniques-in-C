#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"
#include "CaffeinatedBeverage.r"
#include "Coffee.h"

typedef struct CoffeeStruct {
    const CaffeinatedBeverage_Data_Struct base;
    //other class data
} CoffeeStruct;

typedef struct coffeeMemoryPool_t
{
    bool used;
    CoffeeStruct thisCoffee;
} coffeeMemoryPool_t;

static coffeeMemoryPool_t coffeeMemoryPool[MAX_NUM_COFFEE_OBJS] = {0};

static const CaffeinatedBeverage_Interface_Struct interface_dynamic;
static const CaffeinatedBeverage_Interface_Struct interface_static;

static void
coffeeInit( Coffee thisCoffee, CaffeinatedBeverage_Interface interface, char * name){
    ASSERT(thisCoffee && interface && name);
    
    printf("\tInitializing new coffee drink with name: %s\n", name);

    CaffeinatedBeverage_setName((CaffeinatedBeverage)thisCoffee,name);
    *(CaffeinatedBeverage_Interface *)thisCoffee = interface;
}

CaffeinatedBeverage newCoffee_dynamic( char * name ) {
    ASSERT(name);
    
    Coffee newCoffee = (Coffee)calloc(1, sizeof(CoffeeStruct));
    coffeeInit(newCoffee, &interface_dynamic, name);
    return (CaffeinatedBeverage)newCoffee;
}

CaffeinatedBeverage newCoffee_static( char * name ) {
    ASSERT(name);
    
    Coffee newCoffee = NULL;

    for( int i = 0; i < MAX_NUM_COFFEE_OBJS; i++)
    {
        if( coffeeMemoryPool[i].used == false )
        {
            coffeeMemoryPool[i].used = true;
            newCoffee = &coffeeMemoryPool[i].thisCoffee;
            coffeeInit(newCoffee, &interface_static, name);
            break;
        }
    }

    return (CaffeinatedBeverage)newCoffee;
}

static void Coffee_brew(CaffeinatedBeverage super __attribute__((unused))) {
    printf("\tDripping coffee through filter.\n\r");
}

static void Coffee_addCondiments(CaffeinatedBeverage super __attribute__((unused))) {
    printf("\tAdding sugar and milk.\n\r");
}

static void Coffee_addWhip(CaffeinatedBeverage super __attribute__((unused))) {
    printf("\tAdding whip.\n\r");
}

static void coffeeDestroy_dynamic( CaffeinatedBeverage super ) {
    ASSERT(super);    
    free(super);
}

static void coffeeDestroy_static( CaffeinatedBeverage super ) {
    ASSERT(super);    
    for( int i = 0; i < MAX_NUM_COFFEE_OBJS; i++)
    {
        if( (Coffee)super == &coffeeMemoryPool[i].thisCoffee )
        {
            memset(&coffeeMemoryPool[i].thisCoffee, 0, sizeof(CoffeeStruct));
            coffeeMemoryPool[i].used = false;
            super = NULL;
            break;
        }
    }
}

static const CaffeinatedBeverage_Interface_Struct interface_dynamic = {
    Coffee_brew,
    Coffee_addCondiments,
    Coffee_addWhip,
    0,
    coffeeDestroy_dynamic
};

static const CaffeinatedBeverage_Interface_Struct interface_static = {
    Coffee_brew,
    Coffee_addCondiments,
    Coffee_addWhip,
    0,
    coffeeDestroy_static
};