#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servoController.h"

#define MAX_CHARS_NAME 10

typedef struct servoController_t
{
    char name[MAX_CHARS_NAME];
    int angle;
} servoController_t;

servoController
servoControllerCreate( void )
{
    servoController newServoController = (servoController)malloc(sizeof(servoController_t));
    // TODO: Check for null pointer on malloc failure

    return newServoController;
}

void
servoControllerInit( servoController thisServoController, char * name )
{
    printf("\tInitializing new servo controller with name: %s\n", name);
    printf("\tI'm a special servo controller!\n");

    strncpy(thisServoController->name, name, MAX_CHARS_NAME);
    thisServoController->angle = 90;
}

int
servoControllerGetCurrentAngle( servoController thisServoController )
{
    return thisServoController->angle;
}

void
servoControllerMoveTo( servoController thisServoController, int angle )
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