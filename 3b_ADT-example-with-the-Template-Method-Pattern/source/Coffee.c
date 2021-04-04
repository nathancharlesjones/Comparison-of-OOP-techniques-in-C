#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CaffeinatedBeverage.r"
#include "Coffee.h"

typedef struct CoffeeStruct {
    CaffeinatedBeverage_Data_Struct base;
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

void
coffeeInit( Coffee thisCoffee, CaffeinatedBeverage_Interface interface, char * name){
    printf("\tInitializing new coffee drink with name: %s\n", name);

    CaffeinatedBeverage_setName((CaffeinatedBeverage)thisCoffee,name);
    thisCoffee->base.interface = interface;
}

CaffeinatedBeverage newCoffee_dynamic( char * name ) {
    Coffee newCoffee = (Coffee)malloc(sizeof(CoffeeStruct));
    coffeeInit(newCoffee, &interface_dynamic, name);
    return (CaffeinatedBeverage)newCoffee;
}

CaffeinatedBeverage newCoffee_static( char * name ) {
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

static void Coffee_brew(CaffeinatedBeverage super) {
    printf("\tDripping coffee through filter.\n\r");
}

static void Coffee_addCondiments(CaffeinatedBeverage super) {
    printf("\tAdding sugar and milk.\n\r");
}

static void Coffee_addWhip(CaffeinatedBeverage super) {
    printf("\tAdding whip.\n\r");
}

void coffeeDestroy_dynamic( CaffeinatedBeverage super ) {
    free(super);
}

void coffeeDestroy_static( CaffeinatedBeverage super ) {
    for( int i = 0; i < MAX_NUM_COFFEE_OBJS; i++)
    {
        if( (Coffee)super == &coffeeMemoryPool[i].thisCoffee )
        {
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