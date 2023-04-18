#include <stdio.h>
#include "assert.h"
#include "duck.h"
#include "duck_private.h"
#include "rubber.h"

typedef struct Rubber_t
{
	struct Duck_t base;
	duck_size  mySize;
} Rubber_t, *Rubber;

const char * sizeNames[] = {"small", "medium", "large"};

static void rubberShow( p_Duck_t thisDuck );
static void rubberDeinit( p_Duck_t thisDuck );
static void rubberDestroy( p_Duck_t thisDuck );

const struct Duck_interface_struct rubberInterface = {
	.show = rubberShow,
	.deinit = rubberDeinit,
	.destroy = rubberDestroy
};

static void
rubberShow( p_Duck_t thisDuck )
{
	ASSERT(thisDuck && thisDuck->name && thisDuck->vtable && thisDuck->vtable == &rubberInterface);
	Rubber thisRubber = (Rubber)thisDuck;

	// Note: This code accesses the base class member variables directly (i.e. "thisDuck->name").
	// Better abstraction could be provided by adding accessor macros or getter/setter functions 
	// in the private header (see "duck_private.h"), thereby allowing any derived classes the option
	// of being more decoupled from the base class' specific implementation.
	printf("\tHi! I'm a %s rubber duck. My name is %s.\n", sizeNames[thisRubber->mySize], thisDuck->name);
}

static void
rubberDeinit( p_Duck_t thisDuck )
{
	Rubber thisRubber = (Rubber)thisDuck;
	thisRubber->mySize = 0;
}

static void
rubberDestroy( p_Duck_t thisDuck )
{
	Rubber thisRubber = (Rubber)thisDuck;
	free(thisRubber);
}

p_Duck_t
rubberNew( char * name, duck_size size )
{
	ASSERT(name);
	
	Rubber newRubber = (Rubber)calloc(1, sizeof(Rubber_t));
	duckInit((p_Duck_t)newRubber, name);
	newRubber->mySize = size;
	((p_Duck_t)newRubber)->vtable = &rubberInterface;

	return (p_Duck_t)newRubber;
}