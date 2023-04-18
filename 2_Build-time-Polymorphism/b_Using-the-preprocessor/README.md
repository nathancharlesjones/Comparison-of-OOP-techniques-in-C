# Abstract data types (ADT) using Compile-time Substitution

## Description

One limitation of using link-time substitution to implement an abstract data type is that only *one* implementation of that ADT can be used in an entire project. Even though we got to choose which implementation we sent to the linker, the linker will match *any* references to that ADT in *any* source file to that *one* implementation. A slightly more surgical technique is to use the preprocessor (a.k.a. macros) to define within each individual source file which implementation should be used for a given ADT. To accomplish this, we need to make a few changes to our code.

First, since we plan on having multiple implementation of an ADT in our project simultaneously, we need to give each implementation it's own header file and unique names for both the data type and it's functions. In this project, I've added separate .h and .c files for `servoController_special`.

Second, we need to make sure that the functions for each implementation match the pattern `Type_FcnName`, meaning the `Create` function for the `servoController` type should be declared as `servoController_Create` and the same function for the `servoController_special` type should be declared as `servoController_special_Create`

```
// servoController.h
servoController servoController_Create( void );
...

// servoController_special.h
servoController_special servoController_special_Create( void );
...
```

The purpose is so that we can more easily define a macro to replace one type name or function call with another.

Third, within each **source file** where we want to use a generic servo controller, we'll replace any reference to a specific servo controller data type or function with macros that will get replaced when the preprocessor is run. It's important that these macros go in the **source file**, not the header file, so that the macros they define are constrained to just that source file. If we put them in the module's header file, then they would be included in any other file that included that header file and we'd likely run into a scenario where *one* set of macros being used conflicted with another set. This *does* mean that for this technique to work, there can be no references to the ADT in a module's header file; they have to be constrained to the source file.

To start, we'll define a macro that will replace a generic data type, `SERVO_T`, with whatever actual data type is desired. We'll use `SERVO_T` everywhere in our code where we want a generic servo controller and the macro will replace it with whichever one we define at the top of the source file.

```
#ifdef SERVO_SPECIAL
#    define SERVO_T servoController_special
#else
#    define SERVO_T servoController
#endif
...
SERVO_T myServo;
```

By placing `#define SERVO_SPECIAL` above that code, the C preprocessor will change the last line to `servoController_special myServo;`. *Omitting* `#define SERVO_SPECIAL` will cause the last line to read as just `servoController myServo;`.

Lastly, we need a way to call each of the functions (`Create`, `Init`, `GetCurrentAngle`, and `MoveTo`) that allows a macro to construct the actual function call. To do this, we'll create a function-like macro called `SERVO()` that takes the desired function name (`Create`, `Init`, `GetCurrentAngle`, and `MoveTo`) as it's first argument, followed by any arguments that are sent to the actual function. Using our `#ifdef` from above, we can choose whether `SERVO()` prefixes the function name with `servoController` or `servoController_special`.

```
#ifdef SERVO_SPECIAL
#    define SERVO(fcn, ...) servoController_special_## fcn(__VA_ARGS__)
#else
#    define SERVO(fcn, ...) servoController_## fcn(__VA_ARGS__)
#endif

// Declare a generic servo controller variable and allocate memory for it
SERVO_T myServo = SERVO(Create);

// Call the "Init" function for the servo with arguments "myServo" (the actual
// variable) and "My servo" (the printable name for the variable)
SERVO(Init, myServo, "My servo");
```

This macro takes advantage of the concatenation operator (`##`) and [variadic arguments](https://gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html) (the `...` and `__VA_ARGS__` in the macro definition). By placing `#define SERVO_SPECIAL` above that code, the C preprocessor will change the last line to `servoController_special_Init(myServo, "My servo");`. *Omitting* `#define SERVO_SPECIAL` will cause the last line to read as just `servoController_Init(myServo, "My servo");`.

The two header files for `servoController` and `servoController_special` can both be included (since they don't clash) or only one can; I decided to include only one in the example code since it seemed orderly to group it with the other macros that get included by defining/ommitting `#define SERVO_SPECIAL`. I also changed the `#if...#else` slightly to require either `SERVO_SPECIAL` or `SERVO_NORMAL` to be defined; this prevents any accidental default behavior and forces the developer to choose which one they want. An `#error` gets reported if neither is defined.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{
    printf("|__Creating robot arm and leg controllers:\n"); --> |__Creating robot arm and leg controllers:

    robotArm arm = robotArmCreate();
    robotArmInit( arm );                                    --> |__Creating servo controllers:
                                                                    Initializing new servo controller with name: Wrist
                                                                    I'm a special servo controller!
                                                                    Initializing new servo controller with name: Elbow
                                                                    I'm a special servo controller!
                                                                    Initializing new servo controller with name: Shoulder
                                                                    I'm a special servo controller!
                                                                    Initializing new robot arm

    robotLeg leg = robotLegCreate();
    robotLegInit( leg );                                    --> |__Creating servo controllers:
                                                                    Initializing new servo controller with name: Ankle
                                                                    Initializing new servo controller with name: Knee
                                                                    Initializing new servo controller with name: Hip
                                                                    Initializing new robot leg

    printf("|__Moving robot arm:\n");                       --> |__Moving robot arm:
    
    robotArm_moveElbowTo(arm, 90);                          -->     Moving Elbow to 90 degrees, but in a REALLY COOL way.
    robotArm_moveWristTo(arm, 55);                          -->     Moving Wrist to 55 degrees, but in a REALLY COOL way.
    robotArm_moveShoulderTo(arm, 179);                      -->     Moving Shoulder to 179 degrees, but in a REALLY COOL way.

    printf("|__Moving robot leg:\n");                       --> |__Moving robot leg:
    
    robotLeg_moveHipTo(leg, 10);                            -->     Moving Hip to 10 degrees.
    robotLeg_moveAnkleTo(leg, 140);                         -->     Moving Ankle to 140 degrees.

    return 0;
}
```

## References
- [Meta Polymorphism - Jonathan Boccara - Meeting C++ 2020 Opening Keynote](https://www.youtube.com/watch?v=mU_n_ohIHQk&t=3875s&ab_channel=MeetingCpp)