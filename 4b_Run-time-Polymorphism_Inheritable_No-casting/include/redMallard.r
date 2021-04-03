#ifndef RED_MALLARD_R
#define RED_MALLARD_R

#include "mallard.r"

typedef struct redMallard_Interface_Struct * redMallard_Interface;

typedef struct redMallard_t
{
    Mallard_t parentMallard;
} redMallard_t;

typedef struct redMallard_Interface_Struct
{
    Mallard_Interface_Struct parentMallard;
} redMallard_Interface_Struct;

extern redMallard_Interface_Struct redMallardDef;

#endif // RED_MALLARD_R