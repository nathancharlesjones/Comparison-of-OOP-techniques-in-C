#include <stdlib.h>
#include <stdio.h>
#include "CaffeinatedBeverage_Private.h"
#include "Tea.h"

typedef struct TeaStruct {
    CaffeinatedBeverage_Data_Struct base;
    //other class data
} TeaStruct;

static void Tea_brew(CaffeinatedBeverage super) {
    printf("Steeping the tea.\n\r");
}

static void Tea_addCondiments(CaffeinatedBeverage super) {
    printf("Adding lemon.\n\r");
}

static CaffeinatedBeverage_Interface_Struct interface = {
    Tea_brew,
    Tea_addCondiments,
    0
};

CaffeinatedBeverage newTea(void) {
    Tea newTea = (Tea)malloc(sizeof(TeaStruct));
    newTea->base.interface = &interface;
    return (CaffeinatedBeverage)newTea;
}
