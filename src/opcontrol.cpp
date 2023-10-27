#include "main.h"
#include "initialize.h"
#include "functions.h"

void handleDrivetrainControl(void* param) {
    while (1) {
        motorGroup_drivetrainLeft .move(
            controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        motorGroup_drivetrainRight.move(
            controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

        pros::delay(5);
    }
}

void handleIntakeControl(void* param) {
    while (1) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            motor_intake.move(127);
        } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            motor_intake.move(-127);
        } else {
            motor_intake.brake();
        }

        pros::delay(5);
    }
}

void handleCataControl(void* param) {
    while (1) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
            Robot::launchCataOnce();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            Robot::lowerCata();
        }
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) {
            motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        }
        pros::delay(5);
    }
}

void handleControllerDisplay(void* param) {
    while (1) {
        controller.print(0, 0, "Cata Motor Temp:%.f      ", motor_cata.get_temperature());
        pros::delay(50);
    }
}

void handlePistonControl(void* param) {
    while (1) {
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
            Robot::toggleWingsDeployment();
        }

        pros::delay(5);
    }
}

void opcontrol() {
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

    pros::Task task_handleDrivetrainControl(handleDrivetrainControl);
    pros::Task task_handleIntakeControl    (handleIntakeControl    );
    pros::Task task_handleCataControl      (handleCataControl      );
    pros::Task task_handleControllerDisplay(handleControllerDisplay);
    pros::Task task_handlePistonControl    (handlePistonControl    );
}