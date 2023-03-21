#ifndef MALLARD_H
#define MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

typedef enum {RED, BROWN, WHITE} featherColor;

extern void * mallardFromHeapMem;
extern void * mallardFromStaticMem;

// "Create" function requires a featherColor in addition to requirements for Ducks. E.g.:
// void * Bill = duckCreate(mallardFromHeapMem, "Bill", WHITE);

void mallardSetFeatherColor( void * thisMallard, featherColor color );
featherColor mallardGetFeatherColor( void * thisMallard );
const char * mallardGetFeatherColorName( void * thisMallard );
void mallardMigrate( void * thisMallard );

#endif // MALLARD_H