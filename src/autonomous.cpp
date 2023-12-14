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

void auton_close_new() {
    Robot::engageParkingBrake();
    Robot::enableIntake();

    Robot::resetOdometer();
    Robot::accelerate(100, 83, 100);
    Robot::waitUntilLeftDistance(inches(35));
    Robot::creepToDistance(inches(52));

    Robot::resetOdometer();
    Robot::accelerate(-100, -83, 100);
    Robot::waitUntilLeftDistance(inches(-35));
    Robot::creepToDistance(inches(-52));

    //Robot::rotateToHeading()
    Robot::resetOdometer();
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

void auton_close_corner_flick() {
    Robot::setHeading(133.5);

    Robot::deployArm();
    Robot::rotateToHeading(45, true);
    Robot::engageParkingBrake();
    Robot::retractArm();

    Robot::enableIntake();
    Robot::resetOdometer();
    Robot::accelerate(60, 60, 100);
    Robot::waitUntilLeftDistance(inches(12));
    Robot::accelerate(60, 100, 50);
    Robot::waitUntilLeftDistance(inches(39));
    Robot::creepToDistance(inches(52));
    pros::delay(150);

    Robot::resetOdometer();
    Robot::accelerate(-100, -100, 100);
    Robot::waitUntilLeftDistance(inches(-18));
    Robot::creepToDistance(inches(-27));

    Robot::rotateToHeading(255, true);
    Robot::reverseIntake();
    Robot::rotateToHeading(21, true);
    Robot::enableIntake();
    
    Robot::resetOdometer();
    Robot::accelerate(100, 100, 100);
    Robot::waitUntilLeftDistance(inches(12));
    Robot::creepToDistance(inches(21));

    Robot::resetOdometer();
    Robot::accelerate(40, 5, 25);
    Robot::waitUntilLeftDistance(inches(13));
    Robot::brake();

    Robot::resetOdometer();
    Robot::accelerate(-110,  -45, 100);
    Robot::waitUntilLeftDistance(inches(-20));
    Robot::accelerate(-40,  -120, 100);
    Robot::waitUntilLeftDistance(inches(-44));
    Robot::creepToDistance(inches(-54));
    
    Robot::reverseIntake();
    pros::delay(150);

    Robot::accelerate(120, -120, 100);
    pros::delay(150);
    Robot::rotateToHeading(330);
    Robot::deployArm();

    Robot::resetOdometer();
    Robot::accelerate(-45, -45, 200);
    Robot::waitUntilLeftDistance(inches(-7));
    Robot::accelerate(-80, -30, 100);
    Robot::waitUntilLeftDistance(inches(-30));
    Robot::accelerate(-127, -127, 100);
    Robot::waitUntilLeftDistance(inches(-50));
    Robot::creepToDistance(inches(-56));
}

void auton_close_corner_safe() {
    Robot::setHeading(134.5);

    Robot::deployArm();
    Robot::rotateToHeading(45, true);
    Robot::rotateToHeading(135);
    Robot::retractArm();

    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 10);
    Robot::waitUntilLeftDistance(inches(-10));
    Robot::creepToDistance(inches(-18));

    Robot::rotateToHeading(180);

    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 100);
    pros::delay(1000);
    Robot::brake();

    Robot::resetOdometer();
    Robot::moveLift(127);
    Robot::creepToDistance(inches(10));
    Robot::moveLift(0);
    Robot::rotateToHeading(90, true);

    Robot::resetOdometer();
    Robot::engageParkingBrake();
    Robot::accelerate(100, 100, 10);
    pros::delay(2000);
    Robot::brake();

    Robot::rotateToHeading(110);
}

void auton_new_close_corner() {
    Robot::setHeading(134.5);

    Robot::deployRightWing();
    Robot::resetOdometer();
    Robot::accelerate(-70, -100, 100);
}

void auton_far_corner() {
    Robot::moveLift(127);
    pros::delay(300);
    Robot::engageParkingBrake();
    Robot::moveLift(0);
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

    pros::delay(750);
    Robot::brake();
    pros::delay(100);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(6));

    Robot::rotateToHeading(0);

    Robot::resetOdometer();
    Robot::accelerate(100, 100, 100);
    Robot::waitUntilLeftDistance(inches(40));
    Robot::creepToDistance(inches(50));

    Robot::rotateToHeading(270, true);

    Robot::accelerate(40, 25, 100);
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

void auton_new_far_corner() {
    Robot::dropIntake();


    Robot::enableIntake();
    Robot::resetOdometer();
    Robot::creepToDistance(inches(10));

    Robot::resetOdometer();
    Robot::accelerate(-80, -80, 100);
    Robot::waitUntilLeftDistance(inches(-20));
    Robot::creepToDistance(inches(-30));
    
    Robot::rotateToHeading(160);
    Robot::reverseIntake();
    pros::delay(200);

    Robot::rotateToHeading(90, true);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(6));

    Robot::rotateToHeading(330, true);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(-5));

    Robot::deployLeftWing();

    Robot::creepToDistance(inches(-14));
    Robot::rotateToHeading(230, true);

    Robot::rotateToHeading(275);
    Robot::retractLeftWing();

    Robot::rotateToHeading(330);

    Robot::resetOdometer();
    Robot::accelerate(-120, -40, 100);

    pros::delay(1500);
    Robot::brake();
    pros::delay(250);
    Robot::creepToDistance(inches(8));
    Robot::rotateToHeading(0);

    Robot::resetOdometer();
    Robot::accelerate(80, 65, 100);
}

void auton_skills() {
    Robot::setHeading(132.5);

    Robot::deployArm();
    Robot::moveLift(127);

    Robot::resetOdometer();
    Robot::accelerate(-80, -100, 100);
    Robot::waitUntilLeftDistance(inches(-10));
    Robot::creepToDistance(inches(-20));

    Robot::rotateToHeading(83, true);

    Robot::runKickerForTime(35000); // 35000

    Robot::moveLift(-127);
    Robot::engageParkingBrake();
    Robot::retractArm();
    Robot::rotateToHeading(135);

    Robot::resetOdometer();
    Robot::creepToDistance(inches(7));

    pros::Task _ ([=] {
        Robot::runKickerToRotation(7000);
    });
    Robot::reverseIntake();

    Robot::resetOdometer();
    Robot::accelerate(50, 80, 100);
    Robot::waitUntilLeftDistance(inches(29));
    Robot::accelerate(80, 80, 10);
    Robot::waitUntilLeftDistance(inches(80));
    Robot::brake();
    Robot::coastKicker();

    Robot::rotateToHeading(270, true);
    Robot::deployArm();

    Robot::accelerate(-120, -90, 10);

    pros::delay(2500);

    Robot::rotateToHeading(200);
    Robot::accelerate(60, 60, 10);
    pros::delay(500);
    Robot::accelerate(-120, -120, 10);
}

void autonomous() {
    auton_new_close_corner();
}