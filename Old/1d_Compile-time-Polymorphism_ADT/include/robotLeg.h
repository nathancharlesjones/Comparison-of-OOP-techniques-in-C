#ifndef ROBOT_LEG_H
#define ROBOT_LEG_H

typedef struct robotLeg_t * robotLeg;

robotLeg robotLegCreate( void );
void robotLegInit( robotLeg thisRobotLeg );
void robotLeg_moveHipTo( robotLeg thisRobotLeg, int angle );
void robotLeg_moveKneeTo( robotLeg thisRobotLeg, int angle );
void robotLeg_moveAnkleTo( robotLeg thisRobotLeg, int angle );

#endif // ROBOT_LEG_H