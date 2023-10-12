#include "main.h"
#include "initialize.h"
#include "functions.h"

void throwy_auton() {
    Robot::deployIntake();
    Robot::driveBackwardInches(45, 0.0);
    Robot::rotateToHeading(270, true); // face goal
    Robot::reverseIntakeOnce(); // spit out match load
    Robot::launchCataOnce(); // put cata down
    Robot::driveForwardInches (9, 270);
    Robot::deployShtick(); // shtick around triball 1
    Robot::rotateToHeading(0, false);
    Robot::rotateToHeading(90, false); // put front towards goal
    Robot::enableIntake();
    Robot::driveForwardInches(18, 180);
    Robot::retractShtick();
    Robot::driveBackwardInches(26, 180);
    Robot::rotateToHeading(212, false);
    /* pros::Task task{[=] { // launch cata during move
        pros::delay(600);
        Robot::launchCataOnce();
    }}; */
    Robot::driveBackwardInches(40, 200);
}

void pushy_auton() {
    Robot::deployIntake();
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
    Robot::rotateToHeading(110, true);
    Robot::enableIntake();
    Robot::driveBackwardTime(400); // pickup triball 3
    Robot::driveForwardInches(10, 110);
    Robot::rotateToHeading(270, false);
    Robot::reverseIntakeOnce(); // spit out triball 3
    pros::delay(350);
    Robot::rotateToHeading(90, false);
    Robot::deployWings();
    Robot::driveForwardTime(700); // shove everything in
}

void skills_auton() {
    Robot::deployIntake();
    Robot::driveBackwardInches(18, 0);
    Robot::rotateToHeading(225, false);
    Robot::driveBackwardTime(800);
    //Robot::launchCataOnce();
}

void autonomous() {
    throwy_auton();
}