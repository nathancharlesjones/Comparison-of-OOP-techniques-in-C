#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

typedef struct servoController_t * servoController;

servoController servoController_Create( void );
void servoController_Init( servoController thisServoController, char * name );
int servoController_GetCurrentAngle( servoController thisServoController );
void servoController_MoveTo( servoController thisServoController, int angle );

#endif // SERVO_CONTROLLER_H