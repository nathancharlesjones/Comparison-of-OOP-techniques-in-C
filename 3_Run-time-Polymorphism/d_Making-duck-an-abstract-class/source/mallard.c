#include <stdio.h>
#include "assert.h"
#include "duck.h"
#include "duck_private.h"
#include "mallard.h"

typedef struct Mallard_t
{
	struct Duck_t base;
	featherColor  myColor;
} Mallard_t, *Mallard;

char * colors[] = { "white", "red", "brown" };

static void mallardShow( p_Duck_t thisDuck );
static void mallardDeinit( p_Duck_t thisDuck );
static void mallardDestroy( p_Duck_t thisDuck );

const struct Duck_interface_struct mallardInterface = {
	.show = mallardShow,
	.deinit = mallardDeinit,
	.destroy = mallardDestroy
};

static void
mallardShow( p_Duck_t thisDuck )
{
	ASSERT(thisDuck && thisDuck->name && thisDuck->vtable && thisDuck->vtable == &mallardInterface);
	Mallard thisMallard = (Mallard)thisDuck;

	// Note: This code accesses the base class member variables directly (i.e. "thisDuck->name").
	// Better abstraction could be provided by adding accessor macros or getter/setter functions 
	// in the private header (see "duck_private.h"), thereby allowing any derived classes the option
	// of being more decoupled from the base class' specific implementation.
	printf("\tHi! My name is %s and I'm a mallard duck. I have %s feathers.\n", thisDuck->name, colors[thisMallard->myColor]);
}

static void
mallardDeinit( p_Duck_t thisDuck )
{
	Mallard thisMallard = (Mallard)thisDuck;
	thisMallard->myColor = 0;
}

static void
mallardDestroy( p_Duck_t thisDuck )
{
	Mallard thisMallard = (Mallard)thisDuck;
	free(thisMallard);
}

p_Duck_t
mallardNew( char * name, featherColor color )
{
	ASSERT(name);
	
	Mallard newMallard = (Mallard)calloc(1, sizeof(Mallard_t));
	duckInit((p_Duck_t)newMallard, name);
	newMallard->myColor = color;
	((p_Duck_t)newMallard)->vtable = &mallardInterface;

	return (p_Duck_t)newMallard;
}