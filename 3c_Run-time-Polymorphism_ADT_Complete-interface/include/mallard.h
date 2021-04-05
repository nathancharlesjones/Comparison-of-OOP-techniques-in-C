#ifndef MALLARD_H
#define MALLARD_H

#include "duck.h"

#define MAX_NUM_MALLARD_OBJS 10

typedef enum {RED, BROWN, WHITE} featherColor;

extern const char * colorNames[];

typedef struct Mallard_t * Mallard;

extern Duck_Interface mallardFromHeapMem;
extern Duck_Interface mallardFromStaticMem;

// "Create" function requires a featherColor. E.g.:
// Duck Bill = duckCreate(mallardFromHeapMem, "Bill", WHITE);

#endif // MALLARD_H