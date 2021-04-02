#ifndef TEA_H
#define TEA_H

#include "CaffeinatedBeverage.h"

#define MAX_NUM_TEA_OBJS 10

typedef struct TeaStruct * Tea;

CaffeinatedBeverage newTea_dynamic( char * name );
CaffeinatedBeverage newTea_static( char * name );
void teaDestroy_dynamic( CaffeinatedBeverage super );
void teaDestroy_static( CaffeinatedBeverage super );

#endif /*TEA_H*/
