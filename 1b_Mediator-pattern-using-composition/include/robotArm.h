#ifndef ROBOT_ARM_H
#define ROBOT_ARM_H

#include "servoController.h"

typedef struct robotArm_t * robotArm;

robotArm robotArmCreate( void );
void robotArmInit( robotArm thisRobotArm, servoController shoulder, servoController elbow, servoController wrist );
void robotArm_moveShoulderTo( robotArm thisRobotArm, int angle );
void robotArm_moveElbowTo( robotArm thisRobotArm, int angle );
void robotArm_moveWristTo( robotArm thisRobotArm, int angle );

#endif // ROBOT_ARM_H