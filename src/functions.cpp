#include "main.h"
#include "initialize.h"

namespace Robot {

int cata_intake_limit                      = 32000;
int block_intake_limit                     = 29000;
bool isIntakeRetracted                     = true;
bool isShtickDeployed                      = false;
bool isWingsDeployed                       = false;
bool isArmDeployed                         = true;

void moveCataTo(int limit) {
    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    motor_cata.move(127);

    pros::delay(250);

    int time = 0;

    while (odo_cata.get_angle() < limit) {
        pros::delay(3);
        pros::screen::print(pros::E_TEXT_MEDIUM, 2, "%d   ", odo_cata.get_angle());
        time += 1;

        if (time > 1000) {
            motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            break;
        }
    }

    pros::delay(45);

    motor_cata.brake();
}

void blockIntakeAndMatchLoad(int limit) {
    if (motor_cata.get_brake_mode() == pros::E_MOTOR_BRAKE_HOLD) {
        motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
        motor_cata.move(127);
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            pros::delay(5);
        }
        motor_cata.brake();
        return;
    }

    moveCataTo(limit);
}

void blockIntake() {
    pros::Task task{[=] {
        moveCataTo(block_intake_limit);
    }};
}

void relaxCata() {
    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    motor_cata.brake();
}

void launchCataOnce() {
    pros::Task task{[=] {
            motor_cata.move(127);
            pros::delay(100);
            moveCataTo(cata_intake_limit);
    }};
}

void testMotors() {
    motor_left1.move(127);
    pros::delay(250);
    motor_left1.brake();
    pros::delay(250);

    motor_right1.move(127);
    pros::delay(250);
    motor_right1.brake();
    pros::delay(250);

    motor_left2.move(127);
    pros::delay(250);
    motor_left2.brake();
    pros::delay(250);

    motor_right2.move(127);
    pros::delay(250);
    motor_right2.brake();
    pros::delay(250);

    motor_left3.move(127);
    pros::delay(250);
    motor_left3.brake();
    pros::delay(250);

    motor_right3.move(127);
    pros::delay(250);
    motor_right3.brake();
    pros::delay(250);
}

void driveForwardCounts(int counts, double target_heading) {
    motorGroup_drivetrainLeft. tare_position();
    motorGroup_drivetrainRight.tare_position();

    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

    motorGroup_drivetrainLeft. move_voltage(12000);
    motorGroup_drivetrainRight.move_voltage(12000);
    while (motorGroup_drivetrainLeft.get_positions()[0] < counts-750) {
        pros::delay(5);
    }
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainLeft. move_voltage(3000);
    motorGroup_drivetrainRight.move_voltage(3000);
    while (motorGroup_drivetrainLeft.get_positions()[0] < counts-45) {
        pros::delay(5);
    }
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();

    pros::delay(25);
    controller.print(0, 0, "%f          ", motorGroup_drivetrainLeft.get_positions()[0]);
}

void driveForwardInches(double inches, double target_heading) {
    driveForwardCounts(inches * 42.9676812887, target_heading);
}

void driveForwardTime(int ms) {
    motorGroup_drivetrainLeft. move_voltage(7000);
    motorGroup_drivetrainRight.move_voltage(7000);
    pros::delay(ms);
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();
    pros::delay(25);
}

void driveBackwardTime(int ms) {
    motorGroup_drivetrainLeft. move_voltage(-7000);
    motorGroup_drivetrainRight.move_voltage(-7000);
    pros::delay(ms);
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();
    pros::delay(25);
}

void driveBackwardCounts(int counts, double target_heading) {
    motorGroup_drivetrainLeft. tare_position();
    motorGroup_drivetrainRight.tare_position();

    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);

    motorGroup_drivetrainLeft. move_voltage(-12000);
    motorGroup_drivetrainRight.move_voltage(-12000);
    while (motorGroup_drivetrainLeft.get_positions()[0] > -counts+750) {
        pros::delay(5);
    }
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainLeft. move_voltage(-3000);
    motorGroup_drivetrainRight.move_voltage(-3000);
    while (motorGroup_drivetrainLeft.get_positions()[0] > -counts+45) {
        pros::delay(5);
    }
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();

    pros::delay(25);
    controller.print(0, 0, "%f          ", motorGroup_drivetrainLeft.get_positions()[0]);
}

void driveBackwardInches(double inches, double target_heading) {
    driveBackwardCounts(inches * 42.9676812887, target_heading);
}

void rotateToHeading(double target_heading, bool reversed) {
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    double current_heading = imu.get_heading();
    double starting_heading = current_heading;

    int voltage              = reversed? -3500 : 3450;
    int overshoot_correction = reversed? 15 : 10;

    while (1) {
        pros::delay(6);

        current_heading = imu.get_heading();

        motorGroup_drivetrainLeft .move_voltage( voltage);
        motorGroup_drivetrainRight.move_voltage(-voltage);

        if (
            abs(target_heading - current_heading) < overshoot_correction ||
            abs(target_heading - (current_heading + 360)) < overshoot_correction ||
            abs(target_heading - (current_heading - 360)) < overshoot_correction
           ) {
            break;
            }
    }

    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();
    pros::delay(25);
    controller.print(0,0,"%f             ", imu.get_heading());
}

void intakeOnce() {
    pros::Task task{[=] {
            motor_intake.move(127);
        pros::delay(400);
        motor_intake.brake();
    }};
}

void reverseIntakeOnce() {
    pros::Task task{[=] {
        motor_intake.move(-127);
        pros::delay(400);
        motor_intake.brake();
    }};
}

void enableIntake() {
    motor_intake.move(127);
}

void disableIntake() {
    motor_intake.brake();
}

void deployIntake() {
    pros::ADIDigitalOut piston_intake  ({{11, 'e'}});
    piston_intake.set_value(false);
    isIntakeRetracted = false;
}

void retractIntake() {
    pros::ADIDigitalOut piston_intake  ({{11, 'e'}});
    piston_intake.set_value(true);
    isIntakeRetracted = true;
}

void toggleIntakeDeployment() {
    if (isIntakeRetracted) {
        deployIntake();
    } else {
        retractIntake();
    }
}

void deployShtick() {
    pros::ADIDigitalOut piston_shtick  ({{11, 'd'}});
    piston_shtick.set_value(true);
    isShtickDeployed = true;
}

void retractShtick() {
    pros::ADIDigitalOut piston_shtick  ({{11, 'd'}});
    piston_shtick.set_value(false);
    isShtickDeployed = false;
}

void toggleShtickDeployment() {
    if (isShtickDeployed) {
        retractShtick();
    } else {
        deployShtick();
    }
}

void deployWings() {
    pros::ADIDigitalOut piston_wings   ({{11, 'c'}});
    piston_wings.set_value(true);
    isWingsDeployed = true;
}

void retractWings() {
    pros::ADIDigitalOut piston_wings   ({{11, 'c'}});
    piston_wings.set_value(false);
    isWingsDeployed = false;
}

void toggleWingsDeployment() {
    if (isWingsDeployed) {
        retractWings();
    } else {
        deployWings();
    }
}

}