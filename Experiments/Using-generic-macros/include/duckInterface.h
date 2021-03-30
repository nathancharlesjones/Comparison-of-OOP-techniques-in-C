#ifndef DUCK_INTERFACE_H
#define DUCK_INTERFACE_H

#include "duck.h"
#include "mallard.h"
#include "redMallard.h"

#define duckGetName(thisDuck) _Generic((thisDuck),  Duck:       _duckGetName, \
                                                    Mallard:    _mallardGetName, \
                                                    redMallard: _redMallardGetName)(thisDuck)

#define duckQuack(thisDuck) _Generic((thisDuck),    Duck:       _duckQuack, \
                                                    Mallard:    _mallardQuack, \
                                                    redMallard: _redMallardQuack)(thisDuck)

#define duckShow(thisDuck) _Generic((thisDuck),    Duck:        _duckShow, \
                                                   Mallard:     _mallardShow, \
                                                   redMallard:  _redMallardShow)(thisDuck)

#endif // DUCK_INTERFACE