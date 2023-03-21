#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#define MAX_NUM_SERVO_CONTROLLER_OBJS 10

typedef struct servoController_t * servoController;

servoController servoControllerCreate_dynamic( void );
servoController servoControllerCreate_static( void );
void servoControllerInit( servoController thisServoController, char * name );
int servoControllerGetCurrentAngle( servoController thisServoController );
void servoControllerMoveTo( servoController thisServoController, int angle );
void servoControllerDestroy_dynamic( servoController thisServoController );
void servoControllerDestroy_static( servoController thisServoController );

#endif // SERVO_CONTROLLER_H