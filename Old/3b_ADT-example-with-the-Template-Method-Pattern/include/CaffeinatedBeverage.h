#ifndef CAFFEIATED_BEVERAGE_H
#define CAFFEIATED_BEVERAGE_H

typedef struct CaffeinatedBeverage_Data_Struct * CaffeinatedBeverage;

void CaffeinatedBeverage_setName(CaffeinatedBeverage _self, char * name);
char * CaffeinatedBeverage_getName(CaffeinatedBeverage _self);

void CaffeinatedBeverage_prepare(CaffeinatedBeverage _self);
void CaffeinatedBeverage_destroy(CaffeinatedBeverage _self);

#endif /*CAFFEIATED_BEVERAGE_H*/
