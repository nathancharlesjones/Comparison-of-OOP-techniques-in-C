#ifndef RED_MALLARD_INTERFACE_H
#define RED_MALLARD_INTERFACE_H

#include "mallard.h"
#include "redMallard.h"

#define mallardGetColor(thisMallard) _Generic((thisMallard),    Mallard:    _mallardGetColor, \
                                                                redMallard: _redMallardGetColor)(thisMallard)

#define mallardMigrate(thisMallard) _Generic((thisMallard), Mallard:    _mallardMigrate, \
                                                            redMallard: _redMallardMigrate)(thisMallard)

#endif // RED_MALLARD_INTERFACE