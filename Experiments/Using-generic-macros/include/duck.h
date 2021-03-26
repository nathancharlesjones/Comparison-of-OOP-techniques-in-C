#ifndef DUCK_H
#define DUCK_H

#include "mallard.h"
#include "redMallard.h"

typedef struct Duck_t * Duck;

Duck duckCreate( void );
void duckInit( Duck thisDuck, char * name );

void _duckQuack( Duck thisDuck );
#define duckQuack(thisDuck) _Generic((thisDuck),    Duck: _duckQuack, \
                                                    Mallard: mallardQuack, \
                                                    redMallard: redMallardQuack)(thisDuck)

void _duckShow( Duck thisDuck );
#define duckShow(thisDuck) _Generic((thisDuck),    Duck: _duckShow, \
                                                   Mallard: mallardShow, \
                                                   redMallard: redMallardShow)(thisDuck)

#endif // DUCK_H