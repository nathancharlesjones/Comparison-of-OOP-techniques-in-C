#ifndef RED_MALLARD_H
#define RED_MALLARD_H

#define MAX_NUM_RED_MALLARD_OBJS 10

extern void * redMallardFromHeapMem;
extern void * redMallardFromStaticMem;

// "Create" function requires no additional arguments. E.g.:
// void * Mary = duckCreate(redMallardFromHeapMem, "Mary", RED);

#endif // RED_MALLARD_H