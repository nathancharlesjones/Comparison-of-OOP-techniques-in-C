#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "assert.h"
#include "Object.h"
#include "Object.r"

#define	MAGIC	0x0effaced	// magic number for objects
// efface: to make (oneself) modestly or shyly inconspicuous

/*
 *	Object
 */

static void * Object_ctor (void * _self, va_list * app __attribute__((unused)))
{
	return _self;
}

static void * Object_dtor (void * _self)
{
	return _self;
}

static int Object_differ (const void * _self, const void * b)
{
	return _self != b;
}

static int Object_puto (const void * _self, FILE * fp)
{	const struct Class * class = classOf(_self);

	return fprintf(fp, "%s at %p\n", class -> name, _self);
}

const void * classOf (const void * _self)
{	
	struct Object * self = cast(Object, _self);
	return self -> class;
}

size_t sizeOf (const void * _self)
{	const struct Class * class = classOf(_self);

	return class -> size;
}

bool
isA (const void * _self, const void * class)
{
	return _self && classOf(_self) == class;
}

bool
isOf (const void * _self, const void * class)
{
	if (_self)
	{	
		const struct Class * myClass = classOf(_self);

		if (class != Object)
		{
			while (myClass != class)
			{
				if (myClass != Object)
				{
					myClass = super(myClass);
				}
				else
				{
					return 0;
				}
			}
		}
		return 1;
	}
	return 0;
}

#define	isObject(p) \
		({ ASSERT(p); \
		ASSERT(((struct Object *) p) -> magic == MAGIC); p; })

void *
cast (const void * class, const void * _self)
{
	const struct Object * self = isObject(_self);
	const struct Class * myClass = isObject(self -> class);

	if (class != Object)
	{	
		isObject(class);
		while (myClass != class)
		{	
			ASSERT(myClass != Object);	// illegal cast
			myClass = myClass -> super;
		}
	}
	return (void *) self;
}

/*
 *	Class
 */

static void * Class_ctor (void * _self, va_list * app)
{	
	struct Class * self = cast(Class, _self);
	const size_t offset = offsetof(struct Class, ctor);

	self -> name = va_arg(* app, char *);
	self -> super = va_arg(* app, struct Class *);
	self -> size = va_arg(* app, size_t);

	ASSERT(self -> super);

	memcpy((char *) self + offset, (char *) self -> super
					+ offset, sizeOf(self -> super) - offset);
{
	typedef void (* voidf) ();	/* generic function pointer */
	voidf selector;
#ifdef va_copy
	va_list ap; va_copy(ap, * app);
#else
	va_list ap = * app;
#endif
    
	while ((selector = va_arg(ap, voidf)))
	{	voidf method = va_arg(ap, voidf);

		if (selector == (voidf) ctor)
			* (voidf *) & self -> ctor = method;
		else if (selector == (voidf) dtor)
			* (voidf *) & self -> dtor = method;
		else if (selector == (voidf) differ)
			* (voidf *) & self -> differ = method;
		else if (selector == (voidf) puto)
			* (voidf *) & self -> puto = method;
	}
#ifdef va_copy
    va_end(ap);
#endif

	return self;
}}

static void * Class_dtor (void * _self)
{	
	struct Class * self = cast(Class, _self);
	fprintf(stderr, "%s: cannot destroy class\n", self->name);
	return 0;
}

const void * super (const void * _self)
{	
	struct Class * self = cast(Class, _self);
	ASSERT(self && self -> super);
	return self -> super;
}

/*
 *	initialization
 */

static const struct Class _Object;
static const struct Class _Class;

static const struct Class _Object = {
	{ MAGIC, & _Class },
	"Object", & _Object, sizeof(struct Object),
	Object_ctor, Object_dtor, Object_differ, Object_puto
};

static const struct Class _Class = {
	{ MAGIC, & _Class },
	"Class", & _Object, sizeof(struct Class),
	Class_ctor, Class_dtor, Object_differ, Object_puto
};

const void * Object = & _Object;
const void * Class = & _Class;

/*
 *	object management and selectors
 */

void * new (const void * _class, ...)
{	
	struct Object * object;
	va_list ap;
	const struct Class * class = cast(Class, _class);

	ASSERT(class && class -> size);
	object = calloc(1, class -> size);
	ASSERT(object);
	object -> magic = MAGIC;
	object -> class = class;
	va_start(ap, _class);
	object = ctor(object, & ap);
	va_end(ap);
	return object;
}

void delete (void * _self)
{
	if (_self)
		free(dtor(_self));
}

void * ctor (void * _self, va_list * app)
{	const struct Class * class = classOf(_self);

	ASSERT(class -> ctor);
	return class -> ctor(_self, app);
}

void * super_ctor (const void * _class,
				void * _self, va_list * app)
{	const struct Class * superclass = super(_class);

	ASSERT(_self && superclass -> ctor);
	return superclass -> ctor(_self, app);
}

void * dtor (void * _self)
{	const struct Class * class = classOf(_self);

	ASSERT(class -> dtor);
	return class -> dtor(_self);
}

void * super_dtor (const void * _class, void * _self)
{	const struct Class * superclass = super(_class);

	ASSERT(_self && superclass -> dtor);
	return superclass -> dtor(_self);
}

int differ (const void * _self, const void * b)
{	const struct Class * class = classOf(_self);

	ASSERT(class -> differ);
	return class -> differ(_self, b);
}

int super_differ (const void * _class, const void * _self, const void * b)
{	const struct Class * superclass = super(_class);

	ASSERT(_self && superclass -> differ);
	return superclass -> differ(_self, b);
}

int puto (const void * _self, FILE * fp)
{	const struct Class * class = classOf(_self);

	ASSERT(class -> puto);
	return class -> puto(_self, fp);
}

int super_puto (const void * _class, const void * _self, FILE * fp)
{	const struct Class * superclass = super(_class);

	ASSERT(_self && superclass -> puto);
	return superclass -> puto(_self, fp);
}
