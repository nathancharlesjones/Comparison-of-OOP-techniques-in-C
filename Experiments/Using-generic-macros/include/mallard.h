#ifndef MALLARD_H
#define MALLARD_H

typedef enum {RED, BROWN, WHITE} featherColor;

typedef struct Mallard_t * Mallard;

Mallard mallardCreate( void );
void mallardInit( Mallard thisMallard, char * name, featherColor color );

char * mallardGetName( Mallard thisMallard );
void mallardQuack( Mallard thisMallard );
void mallardShow( Mallard thisMallard );

const char * mallardGetColor( Mallard thisMallard );
void mallardMigrate( Mallard thisMallard );

#endif // MALLARD_H