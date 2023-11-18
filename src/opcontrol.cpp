#include "main.h"
#include "initialize.h"
#include "functions.h"

void handleDrivetrainControl(void* param) {
    while (1) {
        Robot::drive(
            controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
            controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)
        );

        pros::delay(5);
    }
}

void handleIntakeControl(void* param) {
    while (1) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            Robot::enableIntake();
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            Robot::reverseIntake();
        } else {
            Robot::disableIntake();
        }

        pros::delay(5);
    }
}

void handleKickerControl(void* param) {
    pros::Motor motor_kicker(6, MOTOR_GEARSET_6);
    while (1) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            motor_kicker.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            motor_kicker.move(127);
        } else {
            motor_kicker.brake();
        }
        pros::delay(5);
    }
}

void handleLiftControl(void* param) {
    int mult = 0;
    while (1) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            mult = 127;
        }
        else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
            mult = -127;
        } else {
            mult = 0;
        }
        Robot::moveLift(mult);
        pros::delay(5);
    }
}

void handlePistonControl(void* param) {
    while (1) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            Robot::disengageParkingBrake();
        } 
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
            Robot::engageParkingBrake();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) {
            Robot::toggleArmDeployment();
        }
        pros::delay(5);
    }
}

void opcontrol() {
    pros::Task task_handleDrivetrainControl(handleDrivetrainControl);
    pros::Task task_handleIntakeControl    (handleIntakeControl    );
    pros::Task task_handleCataControl      (handleKickerControl    );
    pros::Task task_handleLiftControl      (handleLiftControl      );
    pros::Task task_handlePistonConrol     (handlePistonControl    );
    
}