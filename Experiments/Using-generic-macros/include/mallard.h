#ifndef MALLARD_H
#define MALLARD_H

typedef enum {RED, BROWN, WHITE} featherColor;

typedef struct Mallard_t * Mallard;

Mallard mallardCreate( void );
void mallardInit( Mallard thisMallard, char * name, featherColor color );

char * _mallardGetName( Mallard thisMallard );
void _mallardQuack( Mallard thisMallard );
void _mallardShow( Mallard thisMallard );

const char * _mallardGetColor( Mallard thisMallard );
void _mallardMigrate( Mallard thisMallard );

#endif // MALLARD_H