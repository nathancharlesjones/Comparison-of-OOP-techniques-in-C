#ifndef MALLARD_H
#define MALLARD_H

#include "duck.h"

#define MAX_NUM_MALLARD_OBJS 10

#define featherColors(F) \
F(RED, "red") \
F(BROWN, "brown") \
F(WHITE, "white")

#define EXTRACT_ENUM( ID, NAME ) ID, 
typedef enum
{
    featherColors(EXTRACT_ENUM)
    NUM_FEATHERCOLORS,
} featherColor;
#undef EXTRACT_ENUM

extern const char * colorNames[NUM_FEATHERCOLORS];

typedef struct Mallard_t * Mallard;

extern Duck_Interface mallardFromHeapMem;
extern Duck_Interface mallardFromStaticMem;

// "Create" function requires a featherColor. E.g.:
// Duck Bill = duckCreate(mallardFromHeapMem, "Bill", WHITE);

#endif // MALLARD_H