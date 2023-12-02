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
    pros::Motor motor_kicker(6, MOTOR_GEARSET_6);
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        motor_kicker.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        motor_kicker.move(127);
    } else {
        motor_kicker.brake();
    }
}

void handleLiftControl() {
    int mult = 0;
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
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
}

void opcontrol() {
    while (1) {
        handleDrivetrainControl();
        handleIntakeControl();
        handleKickerControl();
        handleLiftControl();
        handlePistonControl();
        pros::delay(5);
    }
}