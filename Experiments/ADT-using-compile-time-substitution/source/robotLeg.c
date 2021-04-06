#include <stdio.h>
#include <stdlib.h>
#include "robotLeg.h"

//#define SERVO_SPECIAL
#ifdef SERVO_SPECIAL
#   include "servoController_special.h"
#   define servoController                 servoController_special
#   define servoControllerCreate           servoController_specialCreate
#   define servoControllerInit             servoController_specialInit
#   define servoControllerGetCurrentAngle  servoController_specialGetCurrentAngle
#   define servoControllerMoveTo           servoController_specialMoveTo
#else
#   include "servoController.h"
#endif

typedef struct robotLeg_t
{
    servoController hip;
    servoController knee;
    servoController ankle;
} robotLeg_t;

robotLeg
robotLegCreate( void )
{
    robotLeg newRobotLeg = (robotLeg)malloc(sizeof(robotLeg_t));
    // TODO: Check for null pointer on malloc failure

    return newRobotLeg;
}

void
robotLegInit( robotLeg thisRobotLeg )
{
    printf("|__Creating servo controllers:\n");

    servoController ankle = servoControllerCreate();
    servoController knee = servoControllerCreate();
    servoController hip = servoControllerCreate();

    servoControllerInit(ankle, "Ankle");
    servoControllerInit(knee, "Knee");
    servoControllerInit(hip, "Hip");

    printf("\tInitializing new robot leg\n");

    thisRobotLeg->hip = hip;
    thisRobotLeg->knee = knee;
    thisRobotLeg->ankle = ankle;
}

void
robotLeg_moveHipTo( robotLeg thisRobotLeg, int angle )
{
    if ( ( servoControllerGetCurrentAngle( thisRobotLeg->knee ) > 155 ) || ( servoControllerGetCurrentAngle( thisRobotLeg->knee ) < 25 ) )
    {
        printf("\tRestricting hip movement to [10, 170] degrees when knee joint is within 25 degrees of its extremes.\n");
        if ( angle > 170 ) angle = 170;
        if ( angle < 10 ) angle = 10;
    }
    servoControllerMoveTo( thisRobotLeg->hip, angle );
}

void
robotLeg_moveKneeTo( robotLeg thisRobotLeg, int angle )
{
    if ( ( servoControllerGetCurrentAngle( thisRobotLeg->hip ) > 170 ) || ( servoControllerGetCurrentAngle( thisRobotLeg->hip ) < 10 ) )
    {
        printf("\tRestricting knee movement to [25, 155] degrees when hip joint is within 10 degrees of its extremes.\n");
        if ( angle > 155 ) angle = 155;
        if ( angle < 25 ) angle = 25;
    }
    if ( ( servoControllerGetCurrentAngle( thisRobotLeg->ankle ) > 130 ) || ( servoControllerGetCurrentAngle( thisRobotLeg->ankle ) < 50 ) )
    {
        printf("\tRestricting knee movement to [30, 150] degrees when ankle joint is within 50 degrees of its extremes.\n");
        if ( angle > 150 ) angle = 150;
        if ( angle < 30 ) angle = 30;
    }
    servoControllerMoveTo( thisRobotLeg->knee, angle );
}

void
robotLeg_moveAnkleTo( robotLeg thisRobotLeg, int angle )
{
    if ( ( servoControllerGetCurrentAngle( thisRobotLeg->knee ) > 150 ) || ( servoControllerGetCurrentAngle( thisRobotLeg->knee ) < 30 ) )
    {
        printf("\tRestricting ankle movement to [50, 130] degrees when knee joint is within 30 degrees of its extremes.\n");
        if ( angle > 130 ) angle = 130;
        if ( angle < 50 ) angle = 50;
    }
    servoControllerMoveTo( thisRobotLeg->ankle, angle );
}