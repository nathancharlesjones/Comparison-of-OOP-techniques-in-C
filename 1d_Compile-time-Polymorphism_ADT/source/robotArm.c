#include <stdio.h>
#include <stdlib.h>
#include "robotArm.h"

#define SERVO_SPECIAL
#if defined SERVO_SPECIAL
#    include "servoController_special.h"
#    define SERVO_T servoController_special
#    define SERVO(fcn, ...) servoController_special_## fcn(__VA_ARGS__)
#elif defined SERVO_NORMAL
#    include "servoController.h"
#    define SERVO_T servoController
#    define SERVO(fcn, ...) servoController_## fcn(__VA_ARGS__)
#else
#    error Servo type not defined!
#endif

typedef struct robotArm_t
{
    SERVO_T shoulder;
    SERVO_T elbow;
    SERVO_T wrist;
} robotArm_t;

robotArm
robotArmCreate( void )
{
    robotArm newRobotArm = (robotArm)malloc(sizeof(robotArm_t));
    // TODO: Check for null pointer on malloc failure

    return newRobotArm;
}

void
robotArmInit( robotArm thisRobotArm )
{
    printf("|__Creating servo controllers:\n");

    SERVO_T wrist = SERVO(Create);
    SERVO_T elbow = SERVO(Create);
    SERVO_T shoulder = SERVO(Create);

    SERVO(Init, wrist, "Wrist");
    SERVO(Init, elbow, "Elbow");
    SERVO(Init, shoulder, "Shoulder");

    printf("\tInitializing new robot arm\n");

    thisRobotArm->shoulder = shoulder;
    thisRobotArm->elbow = elbow;
    thisRobotArm->wrist = wrist;
}

void
robotArm_moveShoulderTo( robotArm thisRobotArm, int angle )
{
    if ( ( SERVO(GetCurrentAngle, thisRobotArm->elbow ) > 155 ) || ( SERVO(GetCurrentAngle, thisRobotArm->elbow ) < 25 ) )
    {
        printf("\tRestricting shoulder movement to [10, 170] degrees when elbow joint is within 25 degrees of its extremes.\n");
        if ( angle > 170 ) angle = 170;
        if ( angle < 10 ) angle = 10;
    }
    SERVO(MoveTo, thisRobotArm->shoulder, angle );
}

void
robotArm_moveElbowTo( robotArm thisRobotArm, int angle )
{
    if ( ( SERVO(GetCurrentAngle, thisRobotArm->shoulder ) > 170 ) || ( SERVO(GetCurrentAngle, thisRobotArm->shoulder ) < 10 ) )
    {
        printf("\tRestricting elbow movement to [25, 155] degrees when shoulder joint is within 10 degrees of its extremes.\n");
        if ( angle > 155 ) angle = 155;
        if ( angle < 25 ) angle = 25;
    }
    if ( ( SERVO(GetCurrentAngle, thisRobotArm->wrist ) > 130 ) || ( SERVO(GetCurrentAngle, thisRobotArm->wrist ) < 50 ) )
    {
        printf("\tRestricting elbow movement to [30, 150] degrees when wrist joint is within 50 degrees of its extremes.\n");
        if ( angle > 150 ) angle = 150;
        if ( angle < 30 ) angle = 30;
    }
    SERVO(MoveTo, thisRobotArm->elbow, angle );
}

void
robotArm_moveWristTo( robotArm thisRobotArm, int angle )
{
    if ( ( SERVO(GetCurrentAngle, thisRobotArm->elbow ) > 150 ) || ( SERVO(GetCurrentAngle, thisRobotArm->elbow ) < 30 ) )
    {
        printf("\tRestricting wrist movement to [50, 130] degrees when elbow joint is within 30 degrees of its extremes.\n");
        if ( angle > 130 ) angle = 130;
        if ( angle < 50 ) angle = 50;
    }
    SERVO(MoveTo, thisRobotArm->wrist, angle );
}