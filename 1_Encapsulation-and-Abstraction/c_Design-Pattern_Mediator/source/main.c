#include <stdio.h>
#include "servoController.h"
#include "robotArm.h"

int
main( void )
{
    printf("|__Creating servo controllers:\n");

    servoController wrist = servoControllerCreate_dynamic();
    servoController elbow = servoControllerCreate_dynamic();
    servoController shoulder = servoControllerCreate_static();

    servoControllerInit(wrist, "Wrist");
    servoControllerInit(elbow, "Elbow");
    servoControllerInit(shoulder, "Shoulder");

    printf("|__Creating robot arm controller:\n");

    robotArm arm = robotArmCreate_static();
    robotArmInit( arm, shoulder, elbow, wrist );

    printf("|__Moving within range of motion:\n");
    
    robotArm_moveElbowTo(arm, 90);
    robotArm_moveWristTo(arm, 55);
    robotArm_moveShoulderTo(arm, 179);

    printf("|__Moving outside range of motion:\n");
    
    robotArm_moveElbowTo(arm, 10);
    robotArm_moveWristTo(arm, 140);

    printf("|__Destroying servo controller objects:\n");

    servoControllerDestroy_dynamic(wrist);
    servoControllerDestroy_dynamic(elbow);
    servoControllerDestroy_static(shoulder);

    printf("|__Destroying robot arm object:\n");

    robotArmDestroy_static(arm);

    return 0;
}