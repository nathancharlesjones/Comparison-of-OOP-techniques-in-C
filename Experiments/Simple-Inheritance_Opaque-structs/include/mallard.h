#ifndef MALLARD_H
#define MALLARD_H

typedef enum {RED, BROWN, WHITE} featherColor;
extern const char * colorNames[];

void * mallardCreate( void );
void mallardInit( void * thisMallard, char * name, featherColor color );
void mallardMigrate( void * thisMallard );

#endif // MALLARD_H