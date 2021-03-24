#ifndef MALLARD_R
#define MALLARD_R

#include "duck.r"

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;

#endif //MALLARD_R