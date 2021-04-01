#include "CaffeinatedBeverage.h"
#include "Tea.h"
#include "Coffee.h"

void main(void) {
    CaffeinatedBeverage Tea1 = newTea();
    CaffeinatedBeverage Coffee1 = newCoffee();
    
    CaffeinatedBeverage_prepare(Tea1);
    CaffeinatedBeverage_prepare(Coffee1);
}
