#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

#define PROS_USE_SIMPLE_NAMES //allows from shorter names from commonly used enums
#define PROS_USE_LITERALS  // allows C++ literals to be used from pros::literals namespace

#include "api.h"

#ifdef __cplusplus
extern "C" {
#endif
void autonomous(void);
void initialize(void);
void disabled(void);
void competition_initialize(void);
void opcontrol(void);
#ifdef __cplusplus
}
#endif //__cplusplus

#ifdef __cplusplus
// incluse C++ only headers here
#endif

#endif // _PROS_MAIN_H_