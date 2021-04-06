#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>

#define ASSERT(expr) \
    do { \
        if( !( expr ) ) printf("\tAssertion failed at " __FILE__ ":%d\n", __LINE__); \
    } while(0)

#endif // ASSERT_H