#include "main.h"
#include "initialize.h"
#include "functions.h"

void auton_close_noWP() {
    Robot::engageParkingBrake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::accelerate(100, 88, 100);
    Robot::waitUntilLeftDistance(inches(35));
    Robot::creepToDistance(inches(50));

    Robot::resetOdometer();
    Robot::accelerate(-50, -50, 100);
    Robot::waitUntilLeftDistance(inches(-18));
    Robot::accelerate(-40, -105, 100);


    Robot::resetOdometer();
    Robot::waitUntilLeftDistance(inches(-20));
    Robot::brake();
    Robot::reverseIntake();

    Robot::resetOdometer();
    Robot::creepToDistance(inches(11));

    Robot::resetOdometer();
    Robot::accelerate(20, 62, 100);
    Robot::waitUntilLeftDistance(inches(4.5));

    Robot::resetOdometer();
    Robot::accelerate(70, 70, 100);
    Robot::waitUntilLeftDistance(inches(22));
    Robot::creepToDistance(inches(31));
}

void auton_close_halfWP() {
    Robot::engageParkingBrake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::accelerate(100, 83, 100);
    Robot::waitUntilLeftDistance(inches(35));
    Robot::creepToDistance(inches(50));

    Robot::resetOdometer();
    Robot::accelerate(-50, -50, 100);
    Robot::waitUntilLeftDistance(inches(-20));

    Robot::resetOdometer();
    Robot::accelerate(-35, -110, 100);
    Robot::waitUntilLeftDistance(inches(-18));

    Robot::resetOdometer();
    Robot::creepToDistance(inches(-8));
    Robot::reverseIntake();

    Robot::accelerate(50, 50, 100);
    Robot::waitUntilLeftDistance(inches(3));

    Robot::deployArm();

    Robot::resetOdometer();
    Robot::creepToDistance(inches(6));

    Robot::rotateToHeading(80, true);

    Robot::resetOdometer();
    Robot::accelerate(60, 30, 100);
    Robot::waitUntilLeftDistance(inches(14));

    Robot::retractArm();

    Robot::resetOdometer();
    Robot::accelerate(30, 60, 100);
    Robot::waitUntilLeftDistance(inches(11));
    Robot::creepToDistance(inches(26));
}

void auton_close_double_triball() {
    Robot::engageParkingBrake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::accelerate(100, 83, 100);
    Robot::waitUntilLeftDistance(inches(35));
    Robot::creepToDistance(inches(50));
    pros::delay(100);

    Robot::rotateToHeading(180, true);

    pros::delay(100);
    Robot::reverseIntakeSlow();
    pros::delay(250);

    Robot::rotateToHeading(270);

    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 50);
    Robot::waitUntilLeftDistance(inches(-6));
    Robot::creepForTime(false, 700);

    pros::delay(100);
    Robot::deployArm();
    pros::delay(100);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(6));
    Robot::rotateToHeading(210, true);

    Robot::resetOdometer();
    Robot::accelerate(100, 100, 100);
    Robot::waitUntilLeftDistance(inches(20));
    Robot::creepToDistance(inches(36));

    Robot::resetOdometer();
    Robot::accelerate(15, 70, 100);
    Robot::waitUntilLeftDistance(inches(12));
    Robot::creepToDistance(inches(16));
}

void auton_far_corner() {
    Robot::engageParkingBrake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::accelerate(90, 100, 100);
    Robot::waitUntilLeftDistance(inches(12));
    Robot::creepToDistance(inches(24));

    pros::delay(100);
    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 100);
    Robot::waitUntilLeftDistance(inches(-23));
    Robot::accelerate(-110, -30, 100);
    Robot::waitUntilLeftDistance(inches(-49));
    Robot::creepToDistance(inches(-61));

    Robot::rotateToHeading(90);

    Robot::reverseIntakeSlow();
    pros::delay(150);

    Robot::resetOdometer();
    Robot::accelerate(-10, -50, 100);
    Robot::waitUntilRightDistance(inches(-4));
    Robot::brake();

    Robot::resetOdometer();
    Robot::accelerate(80, 80, 100);
    Robot::waitUntilLeftDistance(inches(2));
    Robot::creepToDistance(inches(8));

    Robot::deployArm();

    Robot::rotateToHeading(45, true);

    Robot::retractArm();

    Robot::rotateToHeading(290, true);

    Robot::accelerate(-90, -110, 100);

    pros::delay(500);
    Robot::brake();
    pros::delay(100);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(12));
    Robot::rotateToHeading(20);

}

void auton_far_center_rush() {
    Robot::engageParkingBrake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::accelerate(93, 120, 200);
    Robot::waitUntilLeftDistance(inches(40));
    Robot::creepToDistance(inches(50));

    Robot::resetOdometer();
    Robot::accelerate(-13, -100, 10);
    Robot::waitUntilLeftDistance(inches(-4));
    Robot::creepToDistance(inches(-12));
    Robot::reverseIntake();
    Robot::deployArm();

    /* Robot::resetOdometer();
    Robot::accelerate(65, 80, 100);
    Robot::waitUntilLeftDistance(inches(30));
    Robot::creepToDistance(inches(40)); */
}

void auton_skills() {
    Robot::moveLift(127);
    pros::delay(3500);
    Robot::moveLift(0);
    pros::Motor motor_kicker(6, MOTOR_GEARSET_6);
    motor_kicker.move(110);
}

void autonomous() {
    auton_far_center_rush();
}