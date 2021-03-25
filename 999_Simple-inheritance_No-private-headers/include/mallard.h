#ifndef MALLARD_H
#define MALLARD_H

// **NOT GOOD**: The value below is hand-calculated and may not result in proper alignment in memory
#define sizeof_Mallard_t 11

typedef enum {RED, BROWN, WHITE} featherColor;

extern const char * colorNames[];

typedef struct Mallard_t * Mallard;

Mallard mallardCreate( void );
void mallardInit( Mallard thisMallard, char * name, featherColor color );
void mallardShow( Mallard thisMallard );

#endif // MALLARD_H