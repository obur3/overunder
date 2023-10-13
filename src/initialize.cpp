#include "main.h"
#include "initialize.h"
#include "functions.h"

pros::Motor motor_left1  (20, MOTOR_GEARSET_06, true);
pros::Motor motor_left2  (19, MOTOR_GEARSET_06);
pros::Motor motor_left3  (9, MOTOR_GEARSET_06, true);
pros::Motor motor_right1 (13, MOTOR_GEARSET_06);
pros::Motor motor_right2 (15, MOTOR_GEARSET_06, true);
pros::Motor motor_right3 (5, MOTOR_GEARSET_06);

pros::MotorGroup motorGroup_drivetrainLeft ({
    motor_left1,
    motor_left2,
    motor_left3
});

pros::MotorGroup motorGroup_drivetrainRight ({
    motor_right1,
    motor_right2,
    motor_right3
});

pros::IMU imu (7);

pros::Motor motor_intake   (8, MOTOR_GEARSET_06);
pros::Motor motor_cata (17, MOTOR_GEARSET_36);

pros::Rotation odo_cata (18);

pros::Controller controller (pros::E_CONTROLLER_MASTER);

void initialize() {
    Robot::retractIntake();

    motorGroup_drivetrainLeft .set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    motorGroup_drivetrainRight.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);

    motorGroup_drivetrainLeft .set_zero_position (0.0);
    motorGroup_drivetrainRight.set_zero_position(0.0);

    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    imu.reset();
    pros::delay(3000);

    imu.set_data_rate(5);
    pros::delay(6);
    imu.tare();
}

void competition_initialize() {
    initialize();
}

void disabled() {
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();

    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    motor_cata.brake();

    motor_intake.brake();
}