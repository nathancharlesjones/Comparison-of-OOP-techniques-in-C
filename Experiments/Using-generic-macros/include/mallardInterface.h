#ifndef RED_MALLARD_INTERFACE_H
#define RED_MALLARD_INTERFACE_H

#include "mallard.h"
#include "redMallard.h"

#define mallardGetColor(thisMallard) _Generic((thisMallard),    Mallard:    mallardGetColor, \
                                                                redMallard: redMallardGetColor)(thisMallard)

#define mallardMigrate(thisMallard) _Generic((thisMallard), Mallard:    mallardMigrate, \
                                                            redMallard: redMallardMigrate)(thisMallard)

#endif // RED_MALLARD_INTERFACE