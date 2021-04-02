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

static void Coffee_brew(CaffeinatedBeverage super) {
    printf("\tDripping coffee through filter.\n\r");
}

static void Coffee_addCondiments(CaffeinatedBeverage super) {
    printf("\tAdding sugar and milk.\n\r");
}

static void Coffee_addWhip(CaffeinatedBeverage super) {
    printf("\tAdding whip.\n\r");
}

static CaffeinatedBeverage_Interface_Struct interface = {
    Coffee_brew,
    Coffee_addCondiments,
    Coffee_addWhip
};

CaffeinatedBeverage newCoffee_dynamic( char * name ) {
    Coffee newCoffee = (Coffee)malloc(sizeof(CoffeeStruct));
    newCoffee->base.interface = &interface;
    strncpy(newCoffee->base.name, name, MAX_CHARS_NAME);
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
            newCoffee->base.interface = &interface;
            strncpy(newCoffee->base.name, name, MAX_CHARS_NAME);
        }
    }

    return (CaffeinatedBeverage)newCoffee;
}

void coffeeDestroy_dynamic( CaffeinatedBeverage super ) {
    printf("\tDestroying coffee object with name: %s\n", super->name);
    
    caffeinatedBeverageDeinit( super );

    free(super);
}

void coffeeDestroy_static( CaffeinatedBeverage super ) {
    for( int i = 0; i < MAX_NUM_COFFEE_OBJS; i++)
    {
        if( (Coffee)super == &coffeeMemoryPool[i].thisCoffee )
        {
            printf("\tDestroying coffee object with name: %s\n", super->name);    
            caffeinatedBeverageDeinit( super );
            coffeeMemoryPool[i].used = false;
            super = NULL;
        }
    }
}