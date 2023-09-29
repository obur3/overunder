#include "main.h"
#include "initialize.h"
#include "functions.h"

void handleDrivetrainControl(void* param) {
    while (1) {
        motorGroup_drivetrainLeft .move(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
        motorGroup_drivetrainRight.move(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));

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
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { // Launch cata once
            Robot::launchCata(Robot::cata_intake_limit);
        }

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) { // Toggle block intake and match load
            Robot::blockIntakeAndMatchLoad(Robot::block_intake_limit);
        }
        
        pros::delay(5);
    }
}

void handleControllerDisplay(void* param) {
    while (1) {
        //controller.print(0, 0, "Cata Motor Temp:%.f      ", motor_cata.get_temperature());
        //controller.print(0, 0, "%.f             ", motor_cata.get_actual_velocity());
        pros::delay(50);
    }
}

void handleCataMotorSafety() {
    while (1) {
        int i = 0;
        while (motor_cata.get_actual_velocity() == 0) {
            i++;
            pros::delay(5);
            if (4000 == i) {
                motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                controller.rumble(".-.-.-.-");
            }
            controller.print(0, 0, "%.0f, %i", motor_cata.get_actual_velocity(), i);
        }

        pros::delay(5);
    }
}

void opcontrol() {
    pros::delay(1000);

    pros::Task task_handleDrivetrainControl(handleDrivetrainControl);
    pros::Task task_handleIntakeControl(handleIntakeControl);
    pros::Task task_handleCataControl(handleCataControl);
    pros::Task task_handleControllerDisplay(handleControllerDisplay);
    pros::Task task_handleCataMotorSafety(handleCataMotorSafety);
}