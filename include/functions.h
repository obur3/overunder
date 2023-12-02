#include "main.h"
#include "initialize.h"

extern int  inches(double in);

namespace Robot { 
    extern void resetIMU                (void);
    extern void setHeading              (double heading);
    extern void testMotors              (void);
    extern void resetOdometer           (void);
    extern void drive                   (double left, double right);
    extern void accelerate              (double left, double right, int ms);
    extern void brake                   (void);
    extern void waitUntilLeftDistance   (int target_counts);
    extern void waitUntilRightDistance  (int target_counts);
    extern void creepToDistance         (int target_counts);
    extern void creepForTime            (bool isForward, int ms);
    extern void rotateToHeading         (double target_heading, bool reversed=false);
    extern void enableIntake            (void);
    extern void reverseIntake           (void);
    extern void reverseIntakeSlow       (void);
    extern void disableIntake           (void);
    extern void launchKickerOnce        (void);
    extern void launchKickerFast        (void);
    extern void moveLift                (int mult);
 
    extern bool isArmDeployed; 
    extern bool isParkingBrakeEngaged; 
    extern void deployArm               (void);
    extern void retractArm              (void);
    extern void toggleArmDeployment     (void);
    extern void engageParkingBrake      (void);
    extern void disengageParkingBrake   (void);
    extern void toggleParkingBrakeEngage(void);

}