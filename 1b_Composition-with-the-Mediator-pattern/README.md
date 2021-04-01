# Composition with the Mediator Pattern

## Description

In life and software, many objects have a "has a" relationship more than an "is a" relationship. For instance, a car HAS an engine but a swallow IS A bird. The first relationship is often called "composition" (as in, an object is being composed of other objects) while the second is often called "inheritance" (as in, an object is inheriting all of the attributes of the "parent" object and, possibly, adding some of its own). Composition is rather easy to implement at this point since all we need to do is define a object that includes other objects in it's attributes. Along the way, we'll see a design pattern called "mediator".

In this example, we're going to assume that we're trying to control a robotic arm that is composed of three joints (shoulder, elbow, and wrist), each of which is manipulated using a standard servo motor. We've started by creating an object, "servoController", which will encapsulate details about how our servo motors are controlled.

```
// include/servoController.h
typedef struct servoController_t * servoController;
```

In this manner, we could potentially swap out our servo motors for different models and only need to change the implementation in "servoController.c" but not any other part of our program.

Since our robotic arm is composed of three servos, we create this object to have three servoController objects.

```
// source/robotArm.c
typedef struct robotArm_t
{
    servoController shoulder;
    servoController elbow;
    servoController wrist;
} robotArm_t;
```

In this manner, the main program only needs to interface with the "robotArm" object and not the individual servo motors. The robot arm could change out the servo motors for stepper motors and only "robotArm.c" would need to change, not any other part of our program.

```
// source/main.c
robotArm_moveElbowTo(arm, 90);
robotArm_moveWristTo(arm, 55);
```

Additionally, we're going to assume that adjacent joints have restrictions on how far they can travel when one or the other are at an extreme range of motion (e.g. if the elbow is fully bent as far as it can go, then the wrist might not be able to travel _its_ full range of motion without colliding with another object, like the shoulder joint). Thus, our "robotArm" object _mediates_ between the main program and our servos by ensuring only valid commands are sent to each of the individual joints. Instead of blindly passing on all requests for joint movement, it restricts each command to a valid value, based on the current angles of the other joints.

```
// source/robotArm.c
void
robotArm_moveShoulderTo( robotArm thisRobotArm, int angle )
{
    if ( ( servoControllerGetCurrentAngle( thisRobotArm->elbow ) > 155 ) || ( servoControllerGetCurrentAngle( thisRobotArm->elbow ) < 25 ) )
    {
        printf("\tRestricting shoulder movement to [10, 170] degrees when elbow joint is within 25 degrees of its extremes.\n");
        if ( angle > 170 ) angle = 170;
        if ( angle < 10 ) angle = 10;
    }
    servoControllerMoveTo( thisRobotArm->shoulder, angle );
}
```

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{
    printf("|__Creating servo controllers:\n");          -->  |__Creating servo controllers:

    servoController wrist = servoControllerCreate();
    servoController elbow = servoControllerCreate();
    servoController shoulder = servoControllerCreate();

    servoControllerInit(wrist, "Wrist");                 -->      Initializing new servo controller with name: Wrist
    servoControllerInit(elbow, "Elbow");                 -->      Initializing new servo controller with name: Elbow
    servoControllerInit(shoulder, "Shoulder");           -->      Initializing new servo controller with name: Shoulder

    printf("|__Creating robot arm controller:\n");       -->  |__Creating robot arm controller:

    robotArm arm = robotArmCreate();
    robotArmInit( arm, shoulder, elbow, wrist );         -->      Initializing new robot arm

    printf("|__Moving within range of motion:\n");       -->  |__Moving within range of motion:
    
    robotArm_moveElbowTo(arm, 90);                       -->      Moving Elbow to 90 degrees.
    robotArm_moveWristTo(arm, 55);                       -->      Moving Wrist to 55 degrees.
    robotArm_moveShoulderTo(arm, 179);                   -->      Moving Shoulder to 179 degrees.

    printf("|__Moving outside range of motion:\n");      -->  |__Moving outside range of motion:
    
    robotArm_moveElbowTo(arm, 10);                       -->      Restricting elbow movement to [25, 155] degrees when shoulder joint is within 10 degrees of its extremes.
                                                                  Moving Elbow to 25 degrees.
    robotArm_moveWristTo(arm, 140);                      -->      Restricting wrist movement to [50, 130] degrees when elbow joint is within 30 degrees of its extremes.
                                                                  Moving Wrist to 130 degrees.

    return 0;
}
```

## References
- ["Head First Design Patterns"](https://www.amazon.com/Head-First-Design-Patterns-Brain-Friendly/dp/0596007124/ref=sr_1_1?crid=1C1X7G13CZMI5&dchild=1&keywords=head+first+design+patterns&qid=1616758854&sprefix=head+first%2Caps%2C182&sr=8-1), Chapter 7 (called the "Adapter" pattern here)
- ["Design Patterns for Embedded Systems in C"](https://www.amazon.com/Design-Patterns-Embedded-Systems-Engineering/dp/1856177076/ref=sr_1_2?dchild=1&keywords=design+patterns+for+embedded+c&qid=1616758966&sr=8-2), Chapter 3, Section 3.4