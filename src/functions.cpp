#include "main.h"
#include "initialize.h"

pros::Motor motor_left1  (2, MOTOR_GEARSET_06, true);
pros::Motor motor_left2  (3, MOTOR_GEARSET_06, true);
pros::Motor motor_left3  (4, MOTOR_GEARSET_18, true);
pros::Motor motor_right1 (9, MOTOR_GEARSET_06);
pros::Motor motor_right2 (8, MOTOR_GEARSET_06);
pros::Motor motor_right3 (7, MOTOR_GEARSET_18);

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

pros::IMU imu (20);

pros::Motor motor_intake_left (11, MOTOR_GEARSET_18);
pros::Motor motor_intake_right(10, MOTOR_GEARSET_18, true);
pros::MotorGroup motorGroup_intake({
    motor_intake_left,
    motor_intake_right
});

pros::Motor motor_lift(5, MOTOR_GEARSET_36, true);

pros::Motor motor_kicker(6, MOTOR_GEARSET_6, false);
pros::Rotation rot_kicker(18);

int inches(double in) {
    return std::round(in * 44.4);
}

namespace Robot { 

void resetIMU() {
    imu.reset();
    pros::delay(3000);
}

void setHeading(double heading) {
    imu.set_heading(heading);
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

void drive(double left, double right) {
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    motorGroup_drivetrainLeft .move(left);
    motorGroup_drivetrainRight.move(right);
}

void resetOdometer() {
    motorGroup_drivetrainLeft .tare_position();
    motorGroup_drivetrainRight.tare_position();
}

void accelerate(double left, double right, int ms) {
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
    for (int i = 0; i < ms; i+=2) {
        motorGroup_drivetrainLeft .move((left*i)/ms);
        motorGroup_drivetrainRight.move((right*i)/ms);
        pros::delay(2);
    }
}

void brake() {
    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();
    motorGroup_drivetrainLeft.move(0);
    motorGroup_drivetrainRight.move(0);
}

void waitUntilRightDistance(int target_counts) {
    double starting_counts = motor_left2.get_position();

    if (target_counts > starting_counts) {
        while (motor_left2.get_position() < target_counts) {
            pros::delay(5);
            controller.print(0, 0, "%f          ", motor_left1.get_position()/44.4);
        }
    } else {
        while (motor_left2.get_position() > target_counts) {
            pros::delay(5);
            controller.print(0, 0, "%f          ", motor_left1.get_position()/44.4);
        }
    }
}

void waitUntilLeftDistance(int target_counts) {
    double starting_counts = motor_left1.get_position();

    if (target_counts > starting_counts) {
        while (motor_left1.get_position() < target_counts) {
            pros::delay(5);
            controller.print(0, 0, "%f          ", motor_left1.get_position()/44.4);
        }
    } else {
        while (motor_left1.get_position() > target_counts) {
            pros::delay(5);
            controller.print(0, 0, "%f          ", motor_left1.get_position()/44.4);
        }
    }
}

void creepToDistance(int target_counts) {
    int braking_dist = 44;

    double starting_counts = motor_left1.get_position();

    int direction = target_counts > starting_counts ? 1 : -1;

    drive(18 * direction, 18 * direction);
    waitUntilLeftDistance(direction > 0 ? target_counts-braking_dist : target_counts+braking_dist);
    brake();
}

void creepForTime(bool isForward, int ms) {
    double starting_counts = motor_left1.get_position();

    int direction = isForward ? 1 : -1;

    drive(18 * direction, 18 * direction);
    pros::delay(ms);
    brake();
}

void rotateToHeading(double target_heading, bool reversed) {
    double current_heading = imu.get_heading();
    double starting_heading = current_heading;

    int voltage              = reversed? -3500 : 3500;
    int overshoot_correction = reversed? 15 : 15;

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

    Robot::brake();
    pros::delay(200);
    controller.print(0,0,"%f             ", imu.get_heading());
}

void enableIntake() {
    motorGroup_intake.move(127);
}

void reverseIntake() {
    motorGroup_intake.move(-127);
}

void reverseIntakeSlow() {
    motorGroup_intake.move(-80);
}

void disableIntake() {
    motorGroup_intake.brake();
}

void runKicker() {
    motor_kicker.move_voltage(12000);
}

void brakeKicker() {
    motor_kicker.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    motor_kicker.brake();
}

void coastKicker() {
    motor_kicker.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    motor_kicker.brake();
}

void runKickerForTime(int ms) {
    runKicker();
    pros::delay(ms);
    brakeKicker();
}

void resetKickerSensor() {
    rot_kicker.reset_position();
    rot_kicker.set_data_rate(5);
}

void runKickerToRotation(int rotation) {
    runKicker();
    int pos = rot_kicker.get_position();
    while (pos < rotation) {
        pros::delay(6);
        pos = rot_kicker.get_position();
    }
    brakeKicker();
}

void moveLift(int mult) {
    motor_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    motor_lift.move(mult);
    if (mult == 0) {
        motor_lift.brake();
    }
}

pros::ADIDigitalOut piston_arm         ('a', true);
pros::ADIDigitalOut piston_parkingBrake('b', false);
pros::ADIDigitalOut piston_leftWing    ('c', false);
pros::ADIDigitalOut piston_rightWing   ('d', false);

extern bool isArmDeployed         = false;
extern bool isParkingBrakeEngaged = false;
extern bool isWingsDeployed       = false;

void deployArm() {
    isArmDeployed = true;
    piston_arm.set_value(false);
}

void retractArm() {
    isArmDeployed = false;
    piston_arm.set_value(true);
}

void toggleArmDeployment() {
    if (isArmDeployed) {
        retractArm();
    } else {
        deployArm();
    }
}

void engageParkingBrake() {
    isParkingBrakeEngaged = true;
    piston_parkingBrake.set_value(true);
}

void disengageParkingBrake() {
    isParkingBrakeEngaged = false;
    piston_parkingBrake.set_value(false);
}

void toggleParkingBrakeEngage() {
    if (isParkingBrakeEngaged) {
        disengageParkingBrake();
    } else {
        engageParkingBrake();
    }
}

void deployWings() {
    isWingsDeployed = true;
    piston_leftWing .set_value(true);
    piston_rightWing.set_value(true);
}

void retractWings() {
    isWingsDeployed = false;
    piston_leftWing .set_value(false);
    piston_rightWing.set_value(false);
}

void toggleWingDeployment() {
    if (isWingsDeployed) {
        retractWings();
    } else {
        deployWings();
    }
}

}