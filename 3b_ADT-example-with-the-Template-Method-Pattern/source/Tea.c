#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "CaffeinatedBeverage.h"
#include "CaffeinatedBeverage.r"
#include "Tea.h"

typedef struct TeaStruct {
    const CaffeinatedBeverage_Data_Struct base;
    //other class data
} TeaStruct;

typedef struct teaMemoryPool_t
{
    bool used;
    TeaStruct thisTea;
} teaMemoryPool_t;

static teaMemoryPool_t teaMemoryPool[MAX_NUM_TEA_OBJS] = {0};

static const CaffeinatedBeverage_Interface_Struct interface_dynamic;
static const CaffeinatedBeverage_Interface_Struct interface_static;

static void
teaInit( Tea thisTea, CaffeinatedBeverage_Interface interface, char * name){
    printf("\tInitializing new tea drink with name: %s\n", name);

    CaffeinatedBeverage_setName((CaffeinatedBeverage)thisTea,name);
    ((CaffeinatedBeverage)thisTea)->interface = interface;
}

CaffeinatedBeverage newTea_dynamic( char * name ) {
    Tea newTea = (Tea)calloc(1, sizeof(TeaStruct));
    teaInit(newTea, &interface_dynamic, name);
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
            teaInit(newTea, &interface_static, name);
            break;
        }
    }

    return (CaffeinatedBeverage)newTea;
}

static void Tea_brew(CaffeinatedBeverage super __attribute__((unused))) {
    printf("\tSteeping the tea.\n\r");
}

static void Tea_addCondiments(CaffeinatedBeverage super __attribute__((unused))) {
    printf("\tAdding lemon.\n\r");
}

static void Tea_destroyDynamic( CaffeinatedBeverage super ) {
    free(super);
}

static void Tea_destroyStatic( CaffeinatedBeverage super ) {
    for( int i = 0; i < MAX_NUM_TEA_OBJS; i++)
    {
        if( (Tea)super == &teaMemoryPool[i].thisTea )
        {
            memset(&teaMemoryPool[i].thisTea, 0, sizeof(TeaStruct));
            teaMemoryPool[i].used = false;
            super = NULL;
            break;
        }
    }
}

static const CaffeinatedBeverage_Interface_Struct interface_dynamic = {
    Tea_brew,
    Tea_addCondiments,
    0,
    0,
    Tea_destroyDynamic
};

static const CaffeinatedBeverage_Interface_Struct interface_static = {
    Tea_brew,
    Tea_addCondiments,
    0,
    0,
    Tea_destroyStatic
};