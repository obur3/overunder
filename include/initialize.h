#include "main.h"

#ifndef INITIALIZE_H
#define INITIALIZE_H

//PUT MOTOR NAMES HERE

extern pros::Motor motor_left1;
extern pros::Motor motor_left2;
extern pros::Motor motor_left3;
extern pros::Motor motor_right1;
extern pros::Motor motor_right2;
extern pros::Motor motor_right3;

extern pros::MotorGroup motorGroup_drivetrainLeft;
extern pros::MotorGroup motorGroup_drivetrainRight;

extern pros::IMU imu;

extern pros::Motor motor_intake;
extern pros::Motor motor_cata;

extern pros::Rotation odo_cata;

extern pros::Controller controller;

#endif