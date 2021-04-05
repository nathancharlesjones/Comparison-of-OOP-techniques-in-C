#ifndef MALLARD_H
#define MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

typedef enum {RED, BROWN, WHITE} featherColor;

typedef struct Mallard_t * Mallard;

Mallard mallardCreate_dynamic( void );
Mallard mallardCreate_static( void );
void mallardInit( Mallard thisMallard, char * name, featherColor color );
void mallardSetFeatherColor( Mallard thisMallard, featherColor color );
featherColor mallardGetFeatherColor( Mallard thisMallard );
const char * mallardGetFeatherColorName( Mallard thisMallard );
void mallardShow( Mallard thisMallard );
void mallardMigrate( Mallard thisMallard );
void mallardDeinit( Mallard thisMallard );
void mallardDestroy_dynamic( Mallard thisMallard );
void mallardDestroy_static( Mallard thisMallard );

#endif // MALLARD_H