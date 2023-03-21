#ifndef DUCK_H
#define DUCK_H

#define MAX_NUM_DUCK_OBJS 10

extern void * duckFromHeapMem;
extern void * duckFromStaticMem;

// "Create" function requires a string literal name. E.g.:
// void * Bill = duckCreate(duckFromHeapMem, "Bill");
void * duckCreate( void * newDuckType, ... );

void duckSetName( void * thisDuck, char * name );
char * duckGetName( void * thisDuck );
void duckQuack( void * thisDuck );
void duckShow( void * thisDuck );
void duckDestroy( void * thisDuck );

#endif // DUCK_H