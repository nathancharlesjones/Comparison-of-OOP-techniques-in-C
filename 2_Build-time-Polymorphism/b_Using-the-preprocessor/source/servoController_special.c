#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servoController_special.h"

#define MAX_CHARS_NAME 10

typedef struct servoController_special_t
{
    char name[MAX_CHARS_NAME];
    int angle;
} servoController_special_t;

servoController_special
servoController_special_Create( void )
{
    servoController_special newServoController = (servoController_special)malloc(sizeof(servoController_special_t));
    // TODO: Check for null pointer on malloc failure

    return newServoController;
}

void
servoController_special_Init( servoController_special thisServoController, char * name )
{
    printf("\tInitializing new servo controller with name: %s\n", name);
    printf("\tI'm a special servo controller!\n");

    strncpy(thisServoController->name, name, MAX_CHARS_NAME);
    thisServoController->angle = 90;
}

int
servoController_special_GetCurrentAngle( servoController_special thisServoController )
{
    return thisServoController->angle;
}

void
servoController_special_MoveTo( servoController_special thisServoController, int angle )
{
    if ( angle < 0 )
    {
        printf("\t**WARNING**: Desired angle was < 0. Limiting to 0 degrees.\n");
        angle = 0;
    }

    if ( angle > 180 )
    {
        printf("\t**WARNING**: Desired angle was > 180. Limiting to 180 degrees.\n");
        angle = 180;
    }
    
    printf("\tMoving %s to %d degrees, but in a REALLY COOL way.\n", thisServoController->name, angle);

    thisServoController->angle = angle;
}