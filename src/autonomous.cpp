#include "main.h"
#include "initialize.h"
#include "functions.h"

void autonomous() {
    Robot::driveBackwardInches(42, 0.0);
    Robot::rotateToHeading(270, true);
    Robot::reverseIntakeOnce();
    Robot::launchCataOnce();
    // shtick down
    Robot::driveForwardInches (9, 270);
    Robot::rotateToHeading(0, false);
    Robot::enableIntake();
    Robot::driveForwardInches (12, 270);
    Robot::driveBackwardInches(12, 270);
    Robot::rotateToHeading(90, false);
    Robot::driveForwardTime(500);
    Robot::driveBackwardInches(25, 90);
    Robot::rotateToHeading(225, false);
    Robot::driveBackwardInches(51, 45);
    // shitck dwon
    Robot::rotateToHeading(315, false);
    Robot::driveForwardInches(18, 285);
    Robot::rotateToHeading(270, true);
}