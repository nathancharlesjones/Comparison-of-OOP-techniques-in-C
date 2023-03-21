#ifndef COFFEE_H
#define COFFEE_H

#include "CaffeinatedBeverage.h"

#define MAX_NUM_COFFEE_OBJS 10

typedef struct CoffeeStruct * Coffee;

CaffeinatedBeverage newCoffee_dynamic( char * name );
CaffeinatedBeverage newCoffee_static( char * name );

#endif /*COFFEE_H*/
