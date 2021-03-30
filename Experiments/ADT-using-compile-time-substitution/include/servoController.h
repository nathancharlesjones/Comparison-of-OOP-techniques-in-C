#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

typedef struct servoController_t * servoController;

servoController servoControllerCreate( void );
void servoControllerInit( servoController thisServoController, char * name );
int servoControllerGetCurrentAngle( servoController thisServoController );
void servoControllerMoveTo( servoController thisServoController, int angle );

#endif // SERVO_CONTROLLER_H