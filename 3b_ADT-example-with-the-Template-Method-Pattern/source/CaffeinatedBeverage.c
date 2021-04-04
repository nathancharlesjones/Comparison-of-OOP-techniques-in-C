#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CaffeinatedBeverage.h"
#include "CaffeinatedBeverage.r"

void
CaffeinatedBeverage_setName(CaffeinatedBeverage _self, char * name)
{
    strncpy(_self->name, name, MAX_CHARS_NAME);
}

char *
CaffeinatedBeverage_getName(CaffeinatedBeverage _self)
{
    return _self->name;
}

static void CaffeinatedBeverage_boilWater(CaffeinatedBeverage _self) {
    printf("\tBoiling water.\n\r");
}

static void CaffeinatedBeverage_brew(CaffeinatedBeverage _self) {
    if (_self && _self->interface && _self->interface->brew) {
        _self->interface->brew(_self);
    }
}

static void CaffeinatedBeverage_pourInCup(CaffeinatedBeverage _self) {
    printf("\tPouring into cup.\n\r");
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
    printf("|__Making beverage with name: %s\n", _self->name);
    CaffeinatedBeverage_boilWater(_self);
    CaffeinatedBeverage_brew(_self);
    CaffeinatedBeverage_pourInCup(_self);
    CaffeinatedBeverage_addCondiments(_self);
    CaffeinatedBeverage_addWhip(_self);
}

void caffeinatedBeverageDeinit( CaffeinatedBeverage _self ) {
    memset(_self->name,0,sizeof(char)*MAX_CHARS_NAME);
}

void
CaffeinatedBeverage_destroy(CaffeinatedBeverage _self)
{
    if( _self )
    {
        if ( _self->interface && _self->interface->deinit )
        {
            _self->interface->deinit(_self);
        }

        printf("\tDeinitializing caffeinated beverage object with name: %s\n", _self->name);
        memset(_self->name, 0, sizeof(char)*MAX_CHARS_NAME);

        if ( _self->interface && _self->interface->destroy )
        {
            _self->interface->destroy(_self);
        }
    }
}