#ifndef DUCK_INTERFACE_H
#define DUCK_INTERFACE_H

#include "duck.h"
#include "mallard.h"
#include "redMallard.h"

#define duckGetName(thisDuck) _Generic((thisDuck),  Duck:       duckGetName, \
                                                    Mallard:    mallardGetName, \
                                                    redMallard: redMallardGetName)(thisDuck)

#define duckQuack(thisDuck) _Generic((thisDuck),    Duck:       duckQuack, \
                                                    Mallard:    mallardQuack, \
                                                    redMallard: redMallardQuack)(thisDuck)

#define duckShow(thisDuck) _Generic((thisDuck),    Duck:        duckShow, \
                                                   Mallard:     mallardShow, \
                                                   redMallard:  redMallardShow)(thisDuck)

#endif // DUCK_INTERFACE