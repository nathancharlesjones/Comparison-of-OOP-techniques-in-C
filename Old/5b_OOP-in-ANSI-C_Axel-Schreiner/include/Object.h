#ifndef	OBJECT_H
#define	OBJECT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

extern const void * Object;		/* new(Object); */

void * new (const void * class, ...);
void delete (void * self);

const void * classOf (const void * self);
size_t sizeOf (const void * self);
bool isA (const void * _self, const void * class);	// object belongs to class
bool isOf (const void * _self, const void * class);// object derives from class
void * cast (const void * class, const void * _self); // asserts isOf()

void * ctor (void * self, va_list * app);
void * dtor (void * self);
int differ (const void * self, const void * b);
int puto (const void * self, FILE * fp);

extern const void * Class;	/* new(Class, "name", super, size
										sel, meth, ... 0); */

const void * super (const void * self);	/* class' superclass */

#endif
