# Abstract data types (ADT) using Link-time Substitution

## Description

In the [description for the previous project](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/1b_Composition-with-the-Mediator-pattern#description), I mentioned that a benefit of encapsulation was the ability to "swap out our servo motors for different models and [then we] only need to change the implementation in "servoController.c" but not any other part of our program." If we were to do that, the interface described in "servoController.h" could be called an "abstract data type", meaning that it represents a data type for which an implementation has yet to be defined. By implementing this abstract data type in different ways, we can start to build polymorphism into our projects.

In this project there are two implementations of "servoController.h": "servoController.c" and "servoController_special.c". Notice how these two files define the same function in slightly different ways:

```
// source/servoController.c
void
servoControllerMoveTo( servoController thisServoController, int angle )
{
    ...
    printf("\tMoving %s to %d degrees.\n", thisServoController->name, angle);
    thisServoController->angle = angle;
}
```

```
// source/servoController_special.c
void
servoControllerMoveTo( servoController thisServoController, int angle )
{
    ...
    printf("\tMoving %s to %d degrees, but in a REALLY COOL way.\n", thisServoController->name, angle);
    thisServoController->angle = angle;
}
```

We can't include both files in our project since the C compiler would (rightly) give us warning of multiply defining functions (i.e. functions like "servoControllerMoveTo" are defined in BOTH "servoController.c" and "servoController_special.c"). So, instead, we modify our makefile such that only one of the files is sent to the linker.

```
// makefile
# SERVO is used to define which type of servo we want to build our project with.
SERVO ?=
...
ifeq ($(SERVO),normal)
SRC_FILES += \
    source/servoController.c
else ifeq ($(SERVO),special)
SRC_FILES += \
	source/servoController_special.c
else
$(error Unreachable)
endif
```

This part of the makefile says that if the variable SERVO is equal to "normal", then "servoController.c" is included in our project (but not "servoController_special.c"). And if SERVO is equal to "special" then the opposite is true (see [How do I run it?](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/1c_ADT-using-link-time-substitution#how-do-i-run-it) to see how to use this when building the project). In this manner, we can change the behavior of our program by simply changing the implementation of "servoController.h", without ever having to change `main()`.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make SERVO=normal"/"make SERVO=special" or "make clean && make SERVO=normal"/"make clean && make SERVO=special" from the command line.

## Expected output

```
// Compiled using "make SERVO=normal"

// source/main.c
int
main( void )
{
    printf("|__Creating servo controllers:\n");          -->  |__Creating servo controllers:

    servoController wrist = servoControllerCreate_dynamic();
    servoController elbow = servoControllerCreate_dynamic();
    servoController shoulder = servoControllerCreate_static();

    servoControllerInit(wrist, "Wrist");                 -->      Initializing new servo controller with name: Wrist
    servoControllerInit(elbow, "Elbow");                 -->      Initializing new servo controller with name: Elbow
    servoControllerInit(shoulder, "Shoulder");           -->      Initializing new servo controller with name: Shoulder

    printf("|__Creating robot arm controller:\n");       -->  |__Creating robot arm controller:

    robotArm arm = robotArmCreate_static();
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

    printf("|__Destroying servo controller objects:\n"); -->  |__Destroying servo controller objects:

    servoControllerDestroy_dynamic(wrist);               -->      Destroying servoController object with name: Wrist
    servoControllerDestroy_dynamic(elbow);               -->      Destroying servoController object with name: Elbow
    servoControllerDestroy_static(shoulder);             -->      Destroying servoController object with name: Shoulder

    printf("|__Destroying robot arm object:\n");         -->  |__Destroying robot arm object:

    robotArmDestroy_static(arm);                         -->      Destroying robotArm object

    return 0;
}
```

```
// Compiled using "make SERVO=special"

// source/main.c
int
main( void )
{
    printf("|__Creating servo controllers:\n");          -->  |__Creating servo controllers:

    servoController wrist = servoControllerCreate_dynamic();
    servoController elbow = servoControllerCreate_dynamic();
    servoController shoulder = servoControllerCreate_static();

    servoControllerInit(wrist, "Wrist");                 -->      Initializing new servo controller with name: Wrist
                                                                  I'm a special servo controller!
    servoControllerInit(elbow, "Elbow");                 -->      Initializing new servo controller with name: Elbow
                                                                  I'm a special servo controller!
    servoControllerInit(shoulder, "Shoulder");           -->      Initializing new servo controller with name: Shoulder
                                                                  I'm a special servo controller!

    printf("|__Creating robot arm controller:\n");       -->  |__Creating robot arm controller:

    robotArm arm = robotArmCreate_static();
    robotArmInit( arm, shoulder, elbow, wrist );         -->      Initializing new robot arm

    printf("|__Moving within range of motion:\n");       -->  |__Moving within range of motion:
    
    robotArm_moveElbowTo(arm, 90);                       -->      Moving Elbow to 90 degrees, but in a REALLY COOL way.
    robotArm_moveWristTo(arm, 55);                       -->      Moving Wrist to 55 degrees, but in a REALLY COOL way.
    robotArm_moveShoulderTo(arm, 179);                   -->      Moving Shoulder to 179 degrees, but in a REALLY COOL way.

    printf("|__Moving outside range of motion:\n");      -->  |__Moving outside range of motion:
    
    robotArm_moveElbowTo(arm, 10);                       -->      Restricting elbow movement to [25, 155] degrees when shoulder joint is within 10 degrees of its extremes.
                                                                  Moving Elbow to 25 degrees, but in a REALLY COOL way.
    robotArm_moveWristTo(arm, 140);                      -->      Restricting wrist movement to [50, 130] degrees when elbow joint is within 30 degrees of its extremes.
                                                                  Moving Wrist to 130 degrees, but in a REALLY COOL way.    

    printf("|__Destroying servo controller objects:\n"); -->  |__Destroying servo controller objects:

    servoControllerDestroy_dynamic(wrist);               -->      Destroying servoController object with name: Wrist
    servoControllerDestroy_dynamic(elbow);               -->      Destroying servoController object with name: Elbow
    servoControllerDestroy_static(shoulder);             -->      Destroying servoController object with name: Shoulder

    printf("|__Destroying robot arm object:\n");         -->  |__Destroying robot arm object:

    robotArmDestroy_static(arm);                         -->      Destroying robotArm object

    return 0;
}
```

## References
- "Link-Time Substitution" from "TDD for Embedded C", pg 158
- [Meta Polymorphism - Jonathan Boccara - Meeting C++ 2020 Opening Keynote](https://www.youtube.com/watch?v=mU_n_ohIHQk&t=3875s&ab_channel=MeetingCpp)