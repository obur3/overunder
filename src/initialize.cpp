#include "main.h"
#include "initialize.h"
#include "functions.h"

pros::Controller controller (pros::E_CONTROLLER_MASTER);

void initialize() {
    Robot::resetIMU();
    Robot::resetKickerSensor();
}

void competition_initialize() {
    initialize();
}

void disabled() {
}