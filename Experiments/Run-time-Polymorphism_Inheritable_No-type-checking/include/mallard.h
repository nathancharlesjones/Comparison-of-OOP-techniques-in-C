#ifndef MALLARD_H
#define MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

typedef enum {RED, BROWN, WHITE} featherColor;

void * mallardCreate_dynamic( char * name, featherColor color );
void * mallardCreate_static( char * name, featherColor color );
void mallardSetFeatherColor( void * thisMallard, featherColor color );
featherColor mallardGetFeatherColor( void * thisMallard );
const char * mallardGetFeatherColorName( void * thisMallard );
void mallardMigrate( void * thisMallard );

#endif // MALLARD_H