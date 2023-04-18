#ifndef	MALLARD_R
#define	MALLARD_R

#include "duck.r"
#include "mallard.h"

struct Mallard
{
    const struct Duck _;
    featherColor myColor;
};

#define featherColor(mallard) (((struct Mallard *)(mallard)) -> myColor)

void super_migrate (const void * class, const void * self);

struct MallardClass
{
	const struct DuckClass _;
	void (*migrate) (const void * self);
};

#endif
