#ifndef COFFEE_H
#define COFFEE_H

#include "CaffeinatedBeverage.h"

#define MAX_NUM_COFFEE_OBJS 10

typedef struct CoffeeStruct * Coffee;

CaffeinatedBeverage newCoffee_dynamic( char * name );
CaffeinatedBeverage newCoffee_static( char * name );
void coffeeDestroy_dynamic( CaffeinatedBeverage thisCoffee );
void coffeeDestroy_static( CaffeinatedBeverage thisCoffee );

#endif /*COFFEE_H*/
