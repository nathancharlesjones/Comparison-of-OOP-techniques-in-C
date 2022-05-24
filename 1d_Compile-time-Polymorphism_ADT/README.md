# Abstract data types (ADT) using Compile-time Substitution (aka the preprocessor)

- Attempt to use encapsulation and the preprocessor to create an ADT that can be specified for each source file (as opposed to for the entire project, like for link-time substitution)
- Works, but requires that any file which uses the ADT implementation (here, "robotArm" and "robotLeg") CAN'T have any reference to the implementation in it's header file (otherwise, the #define would get shared too far by other files that include "robotArm.h" or "robotLeg.h")
- Feels too constricting to me and too touchy; moving to "Experiments"

## References
- [Meta Polymorphism - Jonathan Boccara - Meeting C++ 2020 Opening Keynote](https://www.youtube.com/watch?v=mU_n_ohIHQk&t=3875s&ab_channel=MeetingCpp)