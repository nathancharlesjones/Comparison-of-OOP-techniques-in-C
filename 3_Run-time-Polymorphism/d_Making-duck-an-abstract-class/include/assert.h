#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ASSERT(expr) \
    do { \
        if( !( expr ) ) assertFailed(__FILE__, __LINE__); \
    } while(0)

static inline void
assertFailed( const char * file, uint32_t line )
{
    fprintf(stderr, "ERROR: Assert failed in %s at line %d\n", file, line);
	exit(-1);
}

#endif // ASSERT_H