#ifndef DUCK_H
#define DUCK_H

#define MAX_NUM_DUCK_OBJS 10

typedef struct Duck_t * Duck;
typedef struct Duck_Interface_Struct const * Duck_Interface;

extern Duck_Interface duckFromHeapMem;
extern Duck_Interface duckFromStaticMem; 

Duck duckCreate( Duck_Interface newDuckType, char * name, ... );
void duckSetName( Duck thisDuck, char * name );
char * duckGetName( Duck thisDuck );
void duckQuack( Duck thisDuck );
void duckShow( Duck thisDuck );
void duckDestroy( Duck thisDuck );

#endif // DUCK_H