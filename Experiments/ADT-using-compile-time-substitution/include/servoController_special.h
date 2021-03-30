#ifndef SERVO_CONTROLLER_SPECIAL_H
#define SERVO_CONTROLLER_SPECIAL_H

typedef struct servoController_special_t * servoController_special;

servoController_special servoController_specialCreate( void );
void servoController_specialInit( servoController_special thisServoController, char * name );
int servoController_specialGetCurrentAngle( servoController_special thisServoController );
void servoController_specialMoveTo( servoController_special thisServoController, int angle );

#endif // SERVO_CONTROLLER_H