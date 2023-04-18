#ifndef TEA_H
#define TEA_H

#include "CaffeinatedBeverage.h"

#define MAX_NUM_TEA_OBJS 10

typedef struct TeaStruct * Tea;

CaffeinatedBeverage newTea_dynamic( char * name );
CaffeinatedBeverage newTea_static( char * name );

#endif /*TEA_H*/
