#ifndef	MALLARD_H
#define	MALLARD_H

#include "duck.h"

typedef enum {RED, BROWN, WHITE} featherColor;

extern const void * Mallard;		/* new(Mallard, name, featherColor) */

void migrate (const void * self);

extern const void * MallardClass;		/* adds migrate */

void initMallard (void);

#endif