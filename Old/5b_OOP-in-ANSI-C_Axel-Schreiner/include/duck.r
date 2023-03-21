#ifndef	DUCK_R
#define	DUCK_R

#include "Object.r"

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

struct Duck
{
	const struct Object _;	/* Duck : Object */
	char name[MAX_CHARS_NAME_WITH_NUL];				/* name */
};

#define	name(duck)	(((struct Duck *)(duck)) -> name)

void super_show (const void * class, const void * self);

struct DuckClass
{
	const struct Class _;			/* DuckClass : Class */
	void (*show) (const void * self);
};

#endif
