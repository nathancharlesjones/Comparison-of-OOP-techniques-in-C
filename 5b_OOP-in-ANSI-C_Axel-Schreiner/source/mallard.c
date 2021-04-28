#include <stdio.h>

#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

static void * Mallard_ctor (void * _self, va_list * app)
{	struct Mallard * self = super_ctor(Mallard, _self, app);

	self -> myColor = va_arg(* app, featherColor);
	return self;
}

static void Mallard_show (const void * _self)
{	const struct Mallard * self = _self;

	printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", name(self), colorNames[self->myColor]);
}

/*
 *	initialization
 */

const void * Mallard;

void initMallard (void)
{
	if (! Mallard)
	{	initDuck();
		Mallard = new(DuckClass, "Mallard",
				Duck, sizeof(struct Mallard),
				ctor, Mallard_ctor,
				show, Mallard_show,
				0);
	}
}
