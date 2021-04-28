#include "assert.h"
#include <string.h>

#include "duck.h"
#include "duck.r"

/*
 *	Duck
 */

static void * Duck_ctor (void * _self, va_list * app)
{	struct Duck * self = super_ctor(Duck, _self, app);

	char * name = va_arg(*app, char *);
    strncpy(self->name, name, MAX_CHARS_NAME);

	return self;
}

static void Duck_show (const void * _self)
{	const struct Duck * self = _self;

	printf("\tHi! My name is %s.\n", self->name);
}

void show (const void * _self)
{	const struct DuckClass * class = classOf(_self);

	ASSERT(class -> show);
	class -> show(_self);
}

void super_show (const void * _class, const void * _self)
{	const struct DuckClass * superclass = super(_class);

	ASSERT(_self && superclass -> show);
	superclass -> show(_self);
}

void quack (const void * _self)
{	const struct Duck * self = _self;

	printf("\t%s: Quack!\n", self->name);
}

/*
 *	DuckClass
 */

static void * DuckClass_ctor (void * _self, va_list * app)
{	struct DuckClass * self
					= super_ctor(DuckClass, _self, app);
	typedef void (* voidf) ();
	voidf selector;
#ifdef va_copy
	va_list ap; va_copy(ap, * app);
#else
	va_list ap = * app;
#endif

	while ((selector = va_arg(ap, voidf)))
	{	voidf method = va_arg(ap, voidf);

		if (selector == (voidf) show)
			* (voidf *) & self -> show = method;
	}
#ifdef va_copy
    va_end(ap);
#endif

	return self;
}

/*
 *	initialization
 */

const void * DuckClass, * Duck;

void initDuck (void)
{
	if (! DuckClass)
		DuckClass = new(Class, "DuckClass",
				Class, sizeof(struct DuckClass),
				ctor, DuckClass_ctor,
				0);
	if (! Duck)
		Duck = new(DuckClass, "Duck",
				Object, sizeof(struct Duck),
				ctor, Duck_ctor,
				show, Duck_show,
				0);
}
