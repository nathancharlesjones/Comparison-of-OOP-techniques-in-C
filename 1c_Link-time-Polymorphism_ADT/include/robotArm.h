#ifndef ROBOT_ARM_H
#define ROBOT_ARM_H

#include "servoController.h"

#define MAX_NUM_ROBOT_ARM_OBJS 10

typedef struct robotArm_t * robotArm;

robotArm robotArmCreate_dynamic( void );
robotArm robotArmCreate_static( void );
void robotArmInit( robotArm thisRobotArm, servoController shoulder, servoController elbow, servoController wrist );
void robotArm_moveShoulderTo( robotArm thisRobotArm, int angle );
void robotArm_moveElbowTo( robotArm thisRobotArm, int angle );
void robotArm_moveWristTo( robotArm thisRobotArm, int angle );
void robotArmDestroy_dynamic( robotArm thisRobotArm );
void robotArmDestroy_static( robotArm thisRobotArm );

#endif // ROBOT_ARM_H