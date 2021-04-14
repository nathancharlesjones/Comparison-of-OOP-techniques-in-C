#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "assert.h"
#include "robotArm.h"
#include "servoController.h"

typedef struct robotArm_t
{
    servoController shoulder;
    servoController elbow;
    servoController wrist;
} robotArm_t;

typedef struct robotArmMemoryPool_t
{
    bool used;
    robotArm_t thisRobotArm;
} robotArmMemoryPool_t;

static robotArmMemoryPool_t robotArmMemoryPool[MAX_NUM_ROBOT_ARM_OBJS] = {0};

robotArm
robotArmCreate_dynamic( void )
{
    robotArm newRobotArm = (robotArm)calloc(1, sizeof(robotArm_t));
    // TODO: Check for null pointer on malloc failure

    return newRobotArm;
}

robotArm
robotArmCreate_static( void )
{
    robotArm newRobotArm = NULL;

    for( int i = 0; i < MAX_NUM_ROBOT_ARM_OBJS; i++)
    {
        if( robotArmMemoryPool[i].used == false )
        {
            robotArmMemoryPool[i].used = true;
            newRobotArm = &robotArmMemoryPool[i].thisRobotArm;
            break;
        }
    }

    return newRobotArm;
}

void
robotArmInit( robotArm thisRobotArm, servoController shoulder, servoController elbow, servoController wrist )
{
    ASSERT(thisRobotArm && shoulder && elbow && wrist);
    
    printf("\tInitializing new robot arm\n");

    thisRobotArm->shoulder = shoulder;
    thisRobotArm->elbow = elbow;
    thisRobotArm->wrist = wrist;
}

void
robotArm_moveShoulderTo( robotArm thisRobotArm, int angle )
{
    ASSERT(thisRobotArm);
    
    if ( ( servoControllerGetCurrentAngle( thisRobotArm->elbow ) > 155 ) || ( servoControllerGetCurrentAngle( thisRobotArm->elbow ) < 25 ) )
    {
        printf("\tRestricting shoulder movement to [10, 170] degrees when elbow joint is within 25 degrees of its extremes.\n");
        if ( angle > 170 ) angle = 170;
        if ( angle < 10 ) angle = 10;
    }
    servoControllerMoveTo( thisRobotArm->shoulder, angle );
}

void
robotArm_moveElbowTo( robotArm thisRobotArm, int angle )
{
    ASSERT(thisRobotArm);
    
    if ( ( servoControllerGetCurrentAngle( thisRobotArm->shoulder ) > 170 ) || ( servoControllerGetCurrentAngle( thisRobotArm->shoulder ) < 10 ) )
    {
        printf("\tRestricting elbow movement to [25, 155] degrees when shoulder joint is within 10 degrees of its extremes.\n");
        if ( angle > 155 ) angle = 155;
        if ( angle < 25 ) angle = 25;
    }
    if ( ( servoControllerGetCurrentAngle( thisRobotArm->wrist ) > 130 ) || ( servoControllerGetCurrentAngle( thisRobotArm->wrist ) < 50 ) )
    {
        printf("\tRestricting elbow movement to [30, 150] degrees when wrist joint is within 50 degrees of its extremes.\n");
        if ( angle > 150 ) angle = 150;
        if ( angle < 30 ) angle = 30;
    }
    servoControllerMoveTo( thisRobotArm->elbow, angle );
}

void
robotArm_moveWristTo( robotArm thisRobotArm, int angle )
{
    ASSERT(thisRobotArm);
    
    if ( ( servoControllerGetCurrentAngle( thisRobotArm->elbow ) > 150 ) || ( servoControllerGetCurrentAngle( thisRobotArm->elbow ) < 30 ) )
    {
        printf("\tRestricting wrist movement to [50, 130] degrees when elbow joint is within 30 degrees of its extremes.\n");
        if ( angle > 130 ) angle = 130;
        if ( angle < 50 ) angle = 50;
    }
    servoControllerMoveTo( thisRobotArm->wrist, angle );
}

void
robotArmDestroy_dynamic( robotArm thisRobotArm )
{
    ASSERT(thisRobotArm);
    
    printf("\tDestroying robotArm object\n");
    memset(thisRobotArm, 0, sizeof(robotArm_t));
    free(thisRobotArm);
}

void
robotArmDestroy_static( robotArm thisRobotArm )
{
    for( int i = 0; i < MAX_NUM_ROBOT_ARM_OBJS; i++)
    {
        if( thisRobotArm == &robotArmMemoryPool[i].thisRobotArm )
        {
            printf("\tDestroying robotArm object\n");
            memset(&robotArmMemoryPool[i].thisRobotArm, 0, sizeof(robotArm_t));
            robotArmMemoryPool[i].used = false;
            thisRobotArm = NULL;
            break;
        }
    }
}