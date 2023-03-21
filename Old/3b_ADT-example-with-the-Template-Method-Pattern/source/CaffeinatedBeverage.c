#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assert.h"
#include "CaffeinatedBeverage.h"
#include "CaffeinatedBeverage.r"

void
CaffeinatedBeverage_setName(CaffeinatedBeverage _self, char * name)
{
    ASSERT(_self && name);

    strncpy(_self->name, name, MAX_CHARS_NAME);
}

char *
CaffeinatedBeverage_getName(CaffeinatedBeverage _self)
{
    ASSERT(_self);

    return _self->name;
}

static void CaffeinatedBeverage_boilWater(CaffeinatedBeverage _self __attribute__((unused))) {
    printf("\tBoiling water.\n\r");
}

static void CaffeinatedBeverage_brew(CaffeinatedBeverage _self) {
    ASSERT(_self && _self->interface);

    if( _self->interface->brew ) {
        _self->interface->brew(_self);
    }
}

static void CaffeinatedBeverage_pourInCup(CaffeinatedBeverage _self __attribute__((unused))) {
    printf("\tPouring into cup.\n\r");
}

static void CaffeinatedBeverage_addCondiments(CaffeinatedBeverage _self) {
    ASSERT(_self && _self->interface);

    if( _self->interface->addCondiments ) {
        _self->interface->addCondiments(_self);
    }
}

static void CaffeinatedBeverage_addWhip(CaffeinatedBeverage _self) {
    ASSERT(_self && _self->interface);

    if( _self->interface->addWhip ) {
        _self->interface->addWhip(_self);
    }
}

void CaffeinatedBeverage_prepare(CaffeinatedBeverage _self) {
    ASSERT(_self);

    printf("|__Making beverage with name: %s\n", _self->name);
    CaffeinatedBeverage_boilWater(_self);
    CaffeinatedBeverage_brew(_self);
    CaffeinatedBeverage_pourInCup(_self);
    CaffeinatedBeverage_addCondiments(_self);
    CaffeinatedBeverage_addWhip(_self);
}

void
CaffeinatedBeverage_destroy(CaffeinatedBeverage _self)
{
    ASSERT(_self && _self->interface);

    if( _self->interface->deinit )
    {
        _self->interface->deinit(_self);
    }

    printf("\tDeinitializing caffeinated beverage object with name: %s\n", _self->name);
    memset(_self->name, 0, sizeof(char)*MAX_CHARS_NAME);

    ASSERT( _self->interface->destroy );
    _self->interface->destroy(_self);
}