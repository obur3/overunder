#include "main.h"
#include "initialize.h"

namespace Robot {

int cata_intake_limit  = 31600;
int block_intake_limit = 29000;

void launchCata(int limit) {
    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    motor_cata.move(127);

    pros::delay(350);

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
        motor_cata.move(100);
        while (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            pros::delay(5);
        }
        motor_cata.brake();
        return;
    }

    launchCata(limit);
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

}