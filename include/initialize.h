#include "main.h"

pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Controller partner (pros::E_CONTROLLER_PARTNER);

pros::Motor frontLeft(1,0);
pros::Motor backLeft(4,0);
pros::Motor_Group leftWheels({frontLeft, backLeft});

pros::Motor frontRight(2,1);
pros::Motor backRight(3,1);
pros::Motor_Group rightWheels({frontRight, backRight});

pros::Motor_Group allWheels({frontRight, backRight, frontLeft, backLeft});

pros::Motor arm(11, 0);
pros::Motor armIntake(20, 0);

pros::ADIDigitalIn intakeSwitch (8);
pros::ADIDigitalIn intakeButton (4);

pros::Imu Inert(9);

pros::ADIDigitalOut rightClownPiston(2,false);
pros::ADIDigitalOut wrongClownPiston(1,false);