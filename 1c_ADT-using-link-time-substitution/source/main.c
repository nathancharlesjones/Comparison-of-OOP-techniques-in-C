#include <stdio.h>
#include "servoController.h"
#include "robotArm.h"

int
main( void )
{
    printf("|__Creating servo controllers:\n");

    servoController wrist = servoControllerCreate();
    servoController elbow = servoControllerCreate();
    servoController shoulder = servoControllerCreate();

    servoControllerInit(wrist, "Wrist");
    servoControllerInit(elbow, "Elbow");
    servoControllerInit(shoulder, "Shoulder");

    printf("|__Creating robot arm controller:\n");

    robotArm arm = robotArmCreate();
    robotArmInit( arm, shoulder, elbow, wrist );

    printf("|__Moving within range of motion:\n");
    
    robotArm_moveElbowTo(arm, 90);
    robotArm_moveWristTo(arm, 55);
    robotArm_moveShoulderTo(arm, 179);

    printf("|__Moving outside range of motion:\n");
    
    robotArm_moveElbowTo(arm, 10);
    robotArm_moveWristTo(arm, 140);

    return 0;
}