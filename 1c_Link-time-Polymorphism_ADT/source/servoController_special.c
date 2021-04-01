#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "servoController.h"

#define MAX_CHARS_NAME 10

typedef struct servoController_t
{
    char name[MAX_CHARS_NAME];
    int angle;
} servoController_t;

typedef struct servoControllerMemoryPool_t
{
    bool used;
    servoController_t thisServoController;
} servoControllerMemoryPool_t;

static servoControllerMemoryPool_t servoControllerMemoryPool[MAX_NUM_SERVO_CONTROLLER_OBJS] = {0};

servoController
servoControllerCreate_dynamic( void )
{
    servoController newServoController = (servoController)malloc(sizeof(servoController_t));
    // TODO: Check for null pointer on malloc failure

    return newServoController;
}

servoController
servoControllerCreate_static( void )
{
    servoController newServoController = NULL;

    for( int i = 0; i < MAX_NUM_SERVO_CONTROLLER_OBJS; i++)
    {
        if( servoControllerMemoryPool[i].used == false )
        {
            servoControllerMemoryPool[i].used = true;
            newServoController = &servoControllerMemoryPool[i].thisServoController;
        }
    }

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
        printf("\t**WARNIG**: Desired angle was < 0. Limiting to 0 degrees.\n");
        angle = 0;
    }

    if ( angle > 180 )
    {
        printf("\t**WARNIG**: Desired angle was > 180. Limiting to 180 degrees.\n");
        angle = 180;
    }
    
    printf("\tMoving %s to %d degrees, but in a REALLY COOL way.\n", thisServoController->name, angle);

    thisServoController->angle = angle;
}

void
servoControllerDestroy_dynamic( servoController thisServoController )
{
    printf("\tDestroying servoController object with name: %s\n", thisServoController->name);
    memset(thisServoController, 0, sizeof(servoController_t));
    free(thisServoController);
}

void
servoControllerDestroy_static( servoController thisServoController )
{
    for( int i = 0; i < MAX_NUM_SERVO_CONTROLLER_OBJS; i++)
    {
        if( thisServoController == &servoControllerMemoryPool[i].thisServoController )
        {
            printf("\tDestroying servoController object with name: %s\n", thisServoController->name);
            memset(&servoControllerMemoryPool[i].thisServoController, 0, sizeof(servoController_t));
            servoControllerMemoryPool[i].used = false;
            thisServoController = NULL;
        }
    }
}