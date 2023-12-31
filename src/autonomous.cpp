#include "main.h"
#include "initialize.h"
#include "functions.h"

void auton_far_4_safe() {
    Robot::dropIntake();
    Robot::enableIntake();


    Robot::resetOdometer();
    Robot::creepToDistance(inches(8));
    pros::delay(200);
    Robot::creepToDistance(inches(4));

    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 100);
    Robot::waitUntilLeftDistance(inches(-12));
    Robot::accelerate(-80, -40, 100);
    Robot::waitUntilLeftDistance(inches(-30));
    Robot::creepToDistance(inches(-48));

    Robot::rotateToHeading(130);
    Robot::reverseIntake();
    Robot::deployWings();
    pros::delay(200);
    Robot::rotateToHeading(80, true);
    Robot::retractWings();
    pros::delay(200);
    Robot::rotateToHeading(35, true);

    Robot::enableIntake();
    Robot::resetOdometer();
    Robot::accelerate(96, 120, 100);
    Robot::waitUntilLeftDistance(inches(30));
    Robot::creepToDistance(inches(43));
    pros::delay(200);

    Robot::rotateToHeading(190);
    Robot::reverseIntakeSlow();

    Robot::resetOdometer();
    Robot::accelerate(120, 50, 100);
    Robot::waitUntilLeftDistance(inches(45));
    Robot::creepToDistance(inches(50));

    Robot::deployArm();
    Robot::rotateToHeading(350);

    Robot::resetOdometer();
    Robot::accelerate(-54, -38, 100);
    Robot::waitUntilLeftDistance(inches(-32));
    Robot::brake();

    Robot::rotateToHeading(270, true);
    Robot::accelerate(-127, -127, 10);
}

void auton_far_touch() {
    Robot::dropIntake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::creepToDistance(inches(8));
    pros::delay(200);
    Robot::creepToDistance(inches(4));

    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 100);
    Robot::waitUntilLeftDistance(inches(-12));
    Robot::accelerate(-80, -40, 100);
    Robot::waitUntilLeftDistance(inches(-30));
    Robot::creepToDistance(inches(-48));

    Robot::rotateToHeading(130);
    Robot::reverseIntake();
    Robot::deployWings();
    pros::delay(200);
    Robot::rotateToHeading(60, true);
    Robot::retractWings();

    Robot::rotateToHeading(300);

    Robot::deployArm();
    Robot::resetOdometer();
    Robot::accelerate(-120, -90, 100);
    pros::delay(1000);
    Robot::brake();
    pros::delay(200);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(8));
    Robot::retractArm();
    Robot::rotateToHeading(355);

    Robot::resetOdometer();
    Robot::accelerate(90, 90, 100);
    pros::delay(1000);
    Robot::deployWings();
}

void autonomous() {
    auton_far_touch();
}