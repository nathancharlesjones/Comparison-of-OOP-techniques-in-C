#include <stdio.h>

#include "assert.h"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

static void *
Mallard_ctor (void * _self, va_list * app)
{	
	struct Mallard * self = super_ctor(Mallard, _self, app);

	self -> myColor = va_arg(* app, featherColor);
	return self;
}

static void
Mallard_show (const void * _self)
{	
	const struct Mallard * self = cast(Mallard, _self);

	printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", name(self), colorNames[self->myColor]);
}

static void
Mallard_migrate (const void * _self)
{	
	const struct Mallard * self = cast(Mallard, _self);

	printf("\t%s: I'm migrating!\n", name(self));
}

void
migrate (const void * _self)
{	
	const struct MallardClass * class = classOf(_self);

	ASSERT(class -> migrate);
	class -> migrate(_self);
}

void
super_migrate (const void * _class, const void * _self)
{	
	const struct MallardClass * superclass = super(_class);

	ASSERT(_self && superclass -> migrate);
	superclass -> migrate(_self);
}

/*
 *  MallardClass
 */

static void *
MallardClass_ctor (void * _self, va_list * app)
{	
	struct MallardClass * self = super_ctor(MallardClass, _self, app);

	typedef void (* voidf) ();
	voidf selector;
#ifdef va_copy
	va_list ap; va_copy(ap, * app);
#else
	va_list ap = * app;
#endif

	while ((selector = va_arg(ap, voidf)))
	{	voidf method = va_arg(ap, voidf);

		if (selector == (voidf) migrate)
		{
			* (voidf *) & self -> migrate = method;
		}
	}
#ifdef va_copy
    va_end(ap);
#endif

	return self;
}

/*
 *	initialization
 */

const void * MallardClass, * Mallard;

void
initMallard (void)
{
	initDuck();
	if (! MallardClass)
	{
		MallardClass = new(DuckClass, "MallardClass", DuckClass, sizeof(struct MallardClass), ctor, MallardClass_ctor, 0);
	}
	if (! Mallard)
	{	
		Mallard = new(MallardClass, "Mallard", Duck, sizeof(struct Mallard), ctor, Mallard_ctor, show, Mallard_show, migrate, Mallard_migrate, 0);
	}
}
