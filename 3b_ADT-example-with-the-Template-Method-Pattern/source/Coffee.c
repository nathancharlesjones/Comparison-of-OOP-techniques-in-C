#include <stdlib.h>
#include <stdio.h>
#include "CaffeinatedBeverage_Private.h"
#include "Coffee.h"

typedef struct CoffeeStruct {
    CaffeinatedBeverage_Data_Struct base;
    //other class data
} CoffeeStruct;

static void Coffee_brew(CaffeinatedBeverage super) {
    printf("Dripping coffee through filter.\n\r");
}

static void Coffee_addCondiments(CaffeinatedBeverage super) {
    printf("Adding sugar and milk.\n\r");
}

static void Coffee_addWhip(CaffeinatedBeverage super) {
    printf("Adding whip.\n\r");
}

static CaffeinatedBeverage_Interface_Struct interface = {
    Coffee_brew,
    Coffee_addCondiments,
    Coffee_addWhip
};

CaffeinatedBeverage newCoffee(void) {
    Coffee newCoffee = (Coffee)malloc(sizeof(CoffeeStruct));
    newCoffee->base.interface = &interface;
    return (CaffeinatedBeverage)newCoffee;
}
