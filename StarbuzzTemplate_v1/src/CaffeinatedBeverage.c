#include <stdlib.h>
#include <stdio.h>
#include "CaffeinatedBeverage.h"
#include "CaffeinatedBeverage_Private.h"

static void CaffeinatedBeverage_boilWater(CaffeinatedBeverage _self) {
    printf("Boiling water.\n\r");
}

static void CaffeinatedBeverage_brew(CaffeinatedBeverage _self) {
    if (_self && _self->interface && _self->interface->brew) {
        _self->interface->brew(_self);
    }
}

static void CaffeinatedBeverage_pourInCup(CaffeinatedBeverage _self) {
    printf("Pouring into cup.\n\r");
}

static void CaffeinatedBeverage_addCondiments(CaffeinatedBeverage _self) {
    if (_self && _self->interface && _self->interface->addCondiments) {
        _self->interface->addCondiments(_self);
    }
}

static void CaffeinatedBeverage_addWhip(CaffeinatedBeverage _self) {
    if (_self && _self->interface && _self->interface->addWhip) {
        _self->interface->addWhip(_self);
    }
}

void CaffeinatedBeverage_prepare(CaffeinatedBeverage _self) {
    CaffeinatedBeverage_boilWater(_self);
    CaffeinatedBeverage_brew(_self);
    CaffeinatedBeverage_pourInCup(_self);
    CaffeinatedBeverage_addCondiments(_self);
    CaffeinatedBeverage_addWhip(_self);
}
