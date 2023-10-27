#include "main.h"
#include "initialize.h"

namespace Robot {

bool isWingsDeployed = false;

void launchCataOnce() {
    pros::Task task{[=] {
            motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            motor_cata.move(127);
            pros::delay(500);
            motor_cata.brake();
            
    }};
}

void matchLoadCata(int times) {
    for (int i=0; i<times; i++) {
        launchCataOnce();
    }
}

void lowerCata() {
    pros::Task task{[=] {
        motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
            motor_cata.move(127);
            pros::delay(250);
            motor_cata.brake();
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

void deployWings() {
    pros::ADIDigitalOut piston_wings  ({{11, 'b'}});
    piston_wings.set_value(true);
    isWingsDeployed = true;
}

void retractWings() {
    pros::ADIDigitalOut piston_wings  ({{11, 'b'}});
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