#include "main.h"
#include "initialize.h"
#include "functions.h"

/* void throwy_auton() {
    Robot::deployIntake();
    Robot::driveBackwardInches(45, 0.0);
    Robot::rotateToHeading(270, true); // face goal
    Robot::reverseIntakeOnce(); // spit out match load
    Robot::driveForwardInches (9, 270);
    Robot::deployWings(); // shtick around triball 1
    Robot::launchCataOnce(); // put cata down
    Robot::rotateToHeading(0, false);
    Robot::rotateToHeading(90, false); // put front towards goal
    Robot::enableIntake();
    Robot::driveForwardTime(500);
    Robot::retractWings();
    Robot::driveBackwardInches(26, 180);
    Robot::rotateToHeading(218, false);
    pros::Task task{[=] { // launch cata during move
        pros::delay(600);
        Robot::launchCataOnce();
    }};
    Robot::driveBackwardInches(54, 200);
}

void pushy_auton() {
    Robot::driveForwardInches(31, 0); // line up with triball 1 and push match load
    Robot::blockIntake();
    Robot::rotateToHeading(90, false); // face intake to triball 1
    Robot::enableIntake();
    Robot::driveBackwardTime(600); // pickup triball 1
    Robot::driveForwardInches(8, 270);
    Robot::rotateToHeading(260, false);
    Robot::reverseIntakeOnce(); // spit out triball 1
    Robot::rotateToHeading(180, true);
    Robot::enableIntake();
    Robot::driveBackwardInches(18, 0); // pickup triball 2
    Robot::rotateToHeading(270, false);
    Robot::reverseIntakeOnce(); // spit out triball 2
    //Robot::rotateToHeading(110, true);
    //Robot::enableIntake();
    //Robot::driveBackwardTime(400); // pickup triball 3
    //Robot::driveForwardInches(10, 110);
    Robot::rotateToHeading(90, false);
    Robot::deployWings();
    Robot::driveForwardTime(700); // shove everything in
}

void skills_auton() {
    Robot::deployIntake();
    pros::delay(250);
    Robot::deployWings();
    pros::delay(250);
    Robot::driveForwardInches(8, 0);
    Robot::matchLoadCata(56);
} */

void autonomous() {
    
}