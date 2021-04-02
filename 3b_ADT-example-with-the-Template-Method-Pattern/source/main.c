#include <stdio.h>
#include "CaffeinatedBeverage.h"
#include "Tea.h"
#include "Coffee.h"

int
main(void)
{
    printf("|__Creating beverage objects\n");

    CaffeinatedBeverage Tea1 = newTea_dynamic("Josephine's tea");
    CaffeinatedBeverage Coffee1 = newCoffee_static("Deidra's coffee");

    printf("|__Preparing beverage objects\n");
    
    CaffeinatedBeverage_prepare(Tea1);
    CaffeinatedBeverage_prepare(Coffee1);

    printf("|__Destroying beverage objects\n");

    teaDestroy_dynamic(Tea1);
    coffeeDestroy_static(Coffee1);

    return 0;
}
