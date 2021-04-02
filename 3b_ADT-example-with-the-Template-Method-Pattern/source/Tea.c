#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CaffeinatedBeverage.r"
#include "Tea.h"

typedef struct TeaStruct {
    CaffeinatedBeverage_Data_Struct base;
    //other class data
} TeaStruct;

typedef struct teaMemoryPool_t
{
    bool used;
    TeaStruct thisTea;
} teaMemoryPool_t;

static teaMemoryPool_t teaMemoryPool[MAX_NUM_TEA_OBJS] = {0};

static void Tea_brew(CaffeinatedBeverage super) {
    printf("\tSteeping the tea.\n\r");
}

static void Tea_addCondiments(CaffeinatedBeverage super) {
    printf("\tAdding lemon.\n\r");
}

static CaffeinatedBeverage_Interface_Struct interface = {
    Tea_brew,
    Tea_addCondiments,
    0
};

CaffeinatedBeverage newTea_dynamic( char * name ) {
    Tea newTea = (Tea)malloc(sizeof(TeaStruct));
    newTea->base.interface = &interface;
    strncpy(newTea->base.name, name, MAX_CHARS_NAME);
    return (CaffeinatedBeverage)newTea;
}

CaffeinatedBeverage newTea_static( char * name ) {
    Tea newTea = NULL;

    for( int i = 0; i < MAX_NUM_TEA_OBJS; i++)
    {
        if( teaMemoryPool[i].used == false )
        {
            teaMemoryPool[i].used = true;
            newTea = &teaMemoryPool[i].thisTea;
            newTea->base.interface = &interface;
            strncpy(newTea->base.name, name, MAX_CHARS_NAME);
        }
    }

    return (CaffeinatedBeverage)newTea;
}

void teaDestroy_dynamic( CaffeinatedBeverage super ) {
    printf("\tDestroying tea object with name: %s\n", super->name);
    
    caffeinatedBeverageDeinit( super );

    free(super);
}

void teaDestroy_static( CaffeinatedBeverage super ) {
    for( int i = 0; i < MAX_NUM_TEA_OBJS; i++)
    {
        if( (Tea)super == &teaMemoryPool[i].thisTea )
        {
            printf("\tDestroying tea object with name: %s\n", super->name);    
            caffeinatedBeverageDeinit( super );
            teaMemoryPool[i].used = false;
            super = NULL;
        }
    }
}