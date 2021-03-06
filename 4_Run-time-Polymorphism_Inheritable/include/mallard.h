#ifndef MALLARD_H
#define MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

typedef enum {RED, BROWN, WHITE} featherColor;
typedef struct Mallard_t * Mallard;

Mallard mallardCreate_dynamic( char * name, featherColor color );
Mallard mallardCreate_static( char * name, featherColor color );
void mallardSetFeatherColor( Mallard thisMallard, featherColor color );
featherColor mallardGetFeatherColor( Mallard thisMallard );
const char * mallardGetFeatherColorName( Mallard thisMallard );
void mallardMigrate( Mallard thisMallard );

#endif // MALLARD_H