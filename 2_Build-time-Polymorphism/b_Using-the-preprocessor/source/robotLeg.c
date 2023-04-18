#include <stdio.h>
#include <stdlib.h>
#include "robotLeg.h"

#define SERVO_NORMAL
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

typedef struct robotLeg_t
{
    SERVO_T hip;
    SERVO_T knee;
    SERVO_T ankle;
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

    SERVO_T ankle = SERVO(Create);
    SERVO_T knee = SERVO(Create);
    SERVO_T hip = SERVO(Create);

    SERVO(Init, ankle, "Ankle");
    SERVO(Init, knee, "Knee");
    SERVO(Init, hip, "Hip");

    printf("\tInitializing new robot leg\n");

    thisRobotLeg->hip = hip;
    thisRobotLeg->knee = knee;
    thisRobotLeg->ankle = ankle;
}

void
robotLeg_moveHipTo( robotLeg thisRobotLeg, int angle )
{
    if ( ( SERVO(GetCurrentAngle, thisRobotLeg->knee ) > 155 ) || ( SERVO(GetCurrentAngle, thisRobotLeg->knee ) < 25 ) )
    {
        printf("\tRestricting hip movement to [10, 170] degrees when knee joint is within 25 degrees of its extremes.\n");
        if ( angle > 170 ) angle = 170;
        if ( angle < 10 ) angle = 10;
    }
    SERVO(MoveTo, thisRobotLeg->hip, angle );
}

void
robotLeg_moveKneeTo( robotLeg thisRobotLeg, int angle )
{
    if ( ( SERVO(GetCurrentAngle, thisRobotLeg->hip ) > 170 ) || ( SERVO(GetCurrentAngle, thisRobotLeg->hip ) < 10 ) )
    {
        printf("\tRestricting knee movement to [25, 155] degrees when hip joint is within 10 degrees of its extremes.\n");
        if ( angle > 155 ) angle = 155;
        if ( angle < 25 ) angle = 25;
    }
    if ( ( SERVO(GetCurrentAngle, thisRobotLeg->ankle ) > 130 ) || ( SERVO(GetCurrentAngle, thisRobotLeg->ankle ) < 50 ) )
    {
        printf("\tRestricting knee movement to [30, 150] degrees when ankle joint is within 50 degrees of its extremes.\n");
        if ( angle > 150 ) angle = 150;
        if ( angle < 30 ) angle = 30;
    }
    SERVO(MoveTo, thisRobotLeg->knee, angle );
}

void
robotLeg_moveAnkleTo( robotLeg thisRobotLeg, int angle )
{
    if ( ( SERVO(GetCurrentAngle, thisRobotLeg->knee ) > 150 ) || ( SERVO(GetCurrentAngle, thisRobotLeg->knee ) < 30 ) )
    {
        printf("\tRestricting ankle movement to [50, 130] degrees when knee joint is within 30 degrees of its extremes.\n");
        if ( angle > 130 ) angle = 130;
        if ( angle < 50 ) angle = 50;
    }
    SERVO(MoveTo, thisRobotLeg->ankle, angle );
}