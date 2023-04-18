#include <stdio.h>
#include "assert.h"
#include "duck.h"
#include "duck_private.h"
#include "mallard.h"

static void
mallardShow( p_Duck_t thisDuck )
{
	ASSERT(thisDuck && thisDuck->name);

	// Note: This code accesses the base class member variables directly (i.e. "thisDuck->name").
	// Better abstraction could be provided by adding accessor macros or getter/setter functions 
	// in the private header (see "duck_private.h"), thereby allowing any derived classes the option
	// of being more decoupled from the base class' specific implementation.
	printf("\tHi! My name is %s and I'm a mallard duck.\n", thisDuck->name);
}

void
mallardInit( p_Duck_t thisDuck )
{
	ASSERT(thisDuck);
	
	thisDuck->duckShow = mallardShow;
}