- Attempt to use encapsulation and the preprocessor to create an ADT that can be specified for each source file (as opposed to for the entire project, like for link-time substitution)
- Works, but requires that any file which uses the ADT implementation (here, "robotArm" and "robotLeg") CAN'T have any reference to the implementation in it's header file (otherwise, the #define would get shared too far by other files that include "robotArm.h" or "robotLeg.h")
- Feels too constricting to me and too touchy; moving to "Experiments"

# Abstract data types (ADT) using Compile-time Substitution (aka the preprocessor)

## Description

One downside of using link-time substitution is that whichever source file we use defines an implementation _for the entire project_. The linker will not allow functions that have the same name, so we are only allowed a single implementation for any given project. For many things, this is perfectly fine. If our ADT was describing an interface for the processor on which our code was to run, it would make sense that there should only be a single implementation for a given executable (since the same executable or binary file is only likely to run on a single processor). However, sometimes we want to be able to use different implementations within a single project. Consider, for example, this project, in which we're extending the idea of controlling a robot arm to that of a robot leg. The robot leg also uses servo motors, like the robot arm, but it's motors are different than those in the robot arm. Using the compile-time substitution (i.e. the C preprocessor), we can specify within _each individual source file_ which servo implementation we want to use, allowing for multiple implementations within the same project.

To do this, we had to make a few changes to our project files.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
|__Creating robot arm and leg controllers:
|__Creating servo controllers:
        Initializing new servo controller with name: Wrist
        I'm a special servo controller!
        Initializing new servo controller with name: Elbow
        I'm a special servo controller!
        Initializing new servo controller with name: Shoulder
        I'm a special servo controller!
        Initializing new robot arm
|__Creating servo controllers:
        Initializing new servo controller with name: Ankle
        Initializing new servo controller with name: Knee
        Initializing new servo controller with name: Hip
        Initializing new robot leg
|__Moving robot arm:
        Moving Elbow to 90 degrees, but in a REALLY COOL way.
        Moving Wrist to 55 degrees, but in a REALLY COOL way.
        Moving Shoulder to 179 degrees, but in a REALLY COOL way.
|__Moving robot leg:
        Moving Hip to 10 degrees.
        Moving Ankle to 140 degrees.
```

## References
- [Meta Polymorphism - Jonathan Boccara - Meeting C++ 2020 Opening Keynote](https://www.youtube.com/watch?v=mU_n_ohIHQk&t=3875s&ab_channel=MeetingCpp)