#ifndef MALLARD_H
#define MALLARD_H

typedef enum {RED, BROWN, WHITE} featherColor;

extern const char * colorNames[];

typedef struct Mallard_t * Mallard;

Mallard mallardCreate( void );
void mallardInit( Mallard thisMallard, char * name, featherColor color );
void mallardMigrate( Mallard thisMallard );

#endif // MALLARD_H