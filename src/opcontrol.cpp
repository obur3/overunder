#include "main.h"
#include "initialize.h"
#include "functions.h"

void handleDrivetrainControl() {
    Robot::drive(
        controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
        controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
    );
}

void handleIntakeControl() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        Robot::enableIntake();
    } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        Robot::reverseIntake();
    } else {
        Robot::disableIntake();
    }
}

void handleKickerControl() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        Robot::runKicker();
    } else {
        Robot::brakeKicker();
    }
}

void handleLiftControl() {
    int mult = 0;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP) ||
        controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        mult = 127;
    }
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        mult = -127;
    } else {
        mult = 0;
    }
    Robot::moveLift(mult);
}

void handlePistonControl() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
        Robot::disengageParkingBrake();
    } 
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        Robot::engageParkingBrake();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
        Robot::toggleArmDeployment();
    }
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        Robot::toggleWingDeployment();
    }
}

void opcontrol() {
    while (1) {
        handleDrivetrainControl();
        handleKickerControl();
        handleIntakeControl();
        handleLiftControl();
        handlePistonControl();
        pros::delay(5);
    }
}