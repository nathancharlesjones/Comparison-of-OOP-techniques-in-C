#ifndef	DUCK_H
#define	Duck_H

#include "Object.h"

extern const void * Duck;			/* new(Duck, name); */

void show (const void * self);
void quack (const void * point);

extern const void * DuckClass;		/* adds quack */

void initDuck (void);

#endif
