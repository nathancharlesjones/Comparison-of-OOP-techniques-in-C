#ifndef SERVO_CONTROLLER_SPECIAL_H
#define SERVO_CONTROLLER_SPECIAL_H

typedef struct servoController_special_t * servoController_special;

servoController_special servoController_special_Create( void );
void servoController_special_Init( servoController_special thisServoController, char * name );
int servoController_special_GetCurrentAngle( servoController_special thisServoController );
void servoController_special_MoveTo( servoController_special thisServoController, int angle );

#endif // SERVO_CONTROLLER_H