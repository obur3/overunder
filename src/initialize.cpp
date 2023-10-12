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

void displaySettingsGUI_3Line() {
    Robot::deployIntake();
    controller.clear();

    int page_index = -1;

    int temp_cata_limit =  Robot::cata_intake_limit;
    int temp_block_limit = Robot::block_intake_limit;

    int event = 0; // 0 none, 1 up, 2 down, 3 y, 4 a

    while (!controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { // Press X to leave menu
        pros::delay(5);
        if (page_index < 0) {
            page_index = 0;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) && page_index > 0) {
            page_index--;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
            page_index++;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))) {
            event = 1;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))) {
            event = 2;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))) {
            event = 3;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))) {
            event = 4;
        } else {
            event = 0;
            continue;
        }

        switch(page_index) {
            case 0:
                pros::delay(50);
                controller.print(0, 0, "0/_ Values Editor:          ");
                pros::delay(50);
                controller.print(1, 0, "(L1/R1) switch page         ");
                pros::delay(50);
                controller.print(2, 0, "(X) exit                    ");
                break;
            case 1: // page 1 Auton Select
                pros::delay(50);
                controller.print(0, 0, "1/_ Auton Select:           ");
                pros::delay(50);
                controller.print(1, 0, "this will do shit           ");
                pros::delay(50);
                controller.print(2, 0, "eventually                  ");
                break;
            case 2: // page 2 Cata Limit Adjust
                if (event==1) { // up
                    temp_cata_limit += 25;
                }
                if (event==2) {
                    temp_cata_limit -= 25;
                }
                if (event==3) {
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                    pros::delay(1000);
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    Robot::moveCataTo(temp_cata_limit);
                }
                if (event==4) {
                    Robot::cata_intake_limit = temp_cata_limit;
                }

                pros::delay(50);
                controller.print(0, 0, "1/_ Cata Limit:             ");
                pros::delay(50);
                controller.print(1, 0, "%s %d                       ",
                                 temp_cata_limit == Robot::cata_intake_limit ? "saved  " : "(a) save",
                                 temp_cata_limit);
                pros::delay(50);
                controller.print(2, 0, "(y) test                    ");
                break;
            case 3: // page 3 Block limit Adjust
                if (event==1) { // up
                    temp_block_limit += 25;
                }
                if (event==2) {
                    temp_block_limit -= 25;
                }
                if (event==3) {
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                    pros::delay(1000);
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    Robot::moveCataTo(temp_block_limit);
                }
                if (event==4) {
                    Robot::block_intake_limit = temp_block_limit;
                }

                pros::delay(50);
                controller.print(0, 0, "1/_ Blocking Limit:         ");
                pros::delay(50);
                controller.print(1, 0, "%s %d                       ",
                                 temp_block_limit == Robot::block_intake_limit ? "saved  " : "(a) save",
                                 temp_block_limit);
                pros::delay(50);
                controller.print(2, 0, "(y) test                    ");
                break;
            default:
                pros::delay(50);
                controller.print(0, 0, "%d/_ NO PAGE                ", page_index);
                pros::delay(50);
                controller.clear_line(1);
                pros::delay(50);
                controller.clear_line(2);
        }
    }

    pros::delay(50);

    controller.clear();
}

void displaySettingsGUI_1Line() {
    int page_index = -1;

    int temp_cata_limit =  Robot::cata_intake_limit;
    int temp_block_limit = Robot::block_intake_limit;

    int event = 0; // 0 none, 1 up, 2 down, 3 y, 4 a

    while (!controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { // Press X to leave menu
        pros::delay(5);
        if (page_index < 0) {
            page_index = 0;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) && page_index > 0) {
            page_index--;
        } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
            page_index++;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP))) {
            event = 1;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN))) {
            event = 2;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y))) {
            event = 3;
        } else if ((controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))) {
            event = 4;
        } else {
            event = 0;
            continue;
        }

        switch(page_index) {
            case 0:
                pros::delay(50);
                controller.print(0, 0, "Settings (L1/R1)     ");
                break;
            case 1: // page 1 Auton Select
                pros::delay(50);
                controller.print(0, 0, "Auton Route: NYI    ");
                break;
            case 2: // page 2 Cata Limit Adjust
                if (event==1) { // up
                    temp_cata_limit += 25;
                }
                if (event==2) {
                    temp_cata_limit -= 25;
                }
                if (event==3) {
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                    pros::delay(1000);
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    Robot::moveCataTo(temp_cata_limit);
                }
                if (event==4) {
                    Robot::cata_intake_limit = temp_cata_limit;
                }

                pros::delay(50);
                controller.print(0, 0, "Cata Limit:%s%d                     ",
                                 temp_cata_limit == Robot::cata_intake_limit ? "" : "x",
                                 temp_cata_limit);
                break;
            case 3: // page 3 Block limit Adjust
                if (event==1) { // up
                    temp_block_limit += 25;
                }
                if (event==2) {
                    temp_block_limit -= 25;
                }
                if (event==3) {
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
                    pros::delay(1000);
                    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
                    Robot::moveCataTo(temp_block_limit);
                }
                if (event==4) {
                    Robot::block_intake_limit = temp_block_limit;
                }

                pros::delay(50);
                controller.print(0, 0, "Block Limit:%s%d                    ",
                                 temp_block_limit == Robot::block_intake_limit ? "" : "x",
                                 temp_block_limit);
                break;
            default:
                pros::delay(50);
                controller.print(0, 0, "NO PAGE                                   ");
        }
    }

    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    pros::delay(250);

    controller.clear_line(0);
}

void printInfo() {
    while (1) {
        printf("%i, %f, %f\n", motorGroup_drivetrainLeft.get_target_velocities()[0], motorGroup_drivetrainLeft.get_actual_velocities()[0], motorGroup_drivetrainLeft.get_positions()[0]);
        pros::delay(10);
    }
}

void initialize() {
    Robot::retractIntake();

    motorGroup_drivetrainLeft .set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);
    motorGroup_drivetrainRight.set_encoder_units(pros::E_MOTOR_ENCODER_COUNTS);

    motorGroup_drivetrainLeft .set_zero_position (0.0);
    motorGroup_drivetrainRight.set_zero_position(0.0);

    motorGroup_drivetrainLeft .set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
    motorGroup_drivetrainRight.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);

    //displaySettingsGUI_3Line();

    //pros::Task task_printInfo (printInfo);
    imu.reset();
    pros::delay(3000);

    imu.set_data_rate(5);
    pros::delay(6);
    imu.tare();
}

void disabled() {
    motorGroup_drivetrainLeft .brake();
    motorGroup_drivetrainRight.brake();

    motor_cata.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    motor_cata.brake();

    motor_intake.brake();
}

void competition_initialize() {
    
}