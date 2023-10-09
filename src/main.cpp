#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize(). If competition control is connected, this will run
 * immediately following autonomous().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

	pros::Controller master (pros::E_CONTROLLER_MASTER);
	


	pros::Motor frontLeft(1);
	pros::Motor backLeft(4);
  pros::Motor_Group leftWheels({frontLeft, backLeft});

	pros::Motor frontRight(2);
	pros::Motor backRight(3);
  pros::Motor_Group rightWheels({frontRight, backRight});


	pros::Motor leftFlywheel(5, 1);
	pros::Motor rightFlywheel(6, 0);
	pros::Motor_Group flywheelMotors({leftFlywheel, rightFlywheel});


	pros::Motor leftIntake(11, 0);
	pros::Motor rightIntake(12, 1);
	pros::Motor_Group intakeMotors({leftIntake, rightIntake});

  //Port #'s
  //1,2,3,4,5,6,7,8
  //A,B,C,D,E,F,G,H
	pros::ADIDigitalOut elevationPiston(5,false);  // defines what port we are using for the elevation pneumatic
	pros::ADIDigitalOut rightClownPiston(3,false); // defines what port we are using for the left plow piston
	pros::ADIDigitalOut wrongClownPiston(8,false); // defines what port we are using for the right plow piston

	
	
  int elevationOn = 1;
  int elevationOff = 1;
  int plow = 1;
  int intakeOff = 1;
  int flywheelOff = 1;
  bool flyWheelOn = false;
  int drvtrDZ;
  int drvtrFB;
  int drvtrLR;


  while (1==1) {

  //Drivetrain Code

   //Defines the values for the left and right joysticks, along with a deadzone where the position of the joysticks does nothing
   //These are put inside of the while loop so that the code can adapt to movements mid-match
    drvtrFB = (pros::E_CONTROLLER_ANALOG_LEFT_Y);
    drvtrLR = (pros::E_CONTROLLER_ANALOG_RIGHT_X);
    drvtrDZ = 10;
   //Makes the motors move by taking the FB and LR values and adding or subtracting them for one another
    if((abs(drvtrFB)>drvtrDZ)||(abs(drvtrFB)>drvtrDZ)){
     // ^^ Checks to see if either joystick has moved out of the deadzone
      rightWheels.move((drvtrFB-drvtrLR)*1.28);
      leftWheels.move((drvtrFB+drvtrLR)*1.28);
      pros::lcd::set_text(2, "Working! :D");
      // https://pros.cs.purdue.edu/v5/api/cpp/motors.html#move

    }else{
      rightWheels.brake();
      leftWheels.brake();
    }

  // Elevation Code -- Building in Progress
  
   // Checks for button pressing and if the Fixed Pneumatic code hasn't been
   // activated
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) == true) && (elevationOn != 2)) {
      elevationPiston.set_value(true);
      elevationOff = 0;
    }  else if(elevationOn == 1){
      elevationPiston.set_value(false);
      if (elevationOff == 0) {

        
        elevationOff = 1;
      }
    }
   // Checks for B button being pressed and lockes the code to keep the
   // pneumatic fixed in place
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) == true) || (elevationOn == 2)) {
      elevationPiston.set_value(true);
      elevationOn = 2;
    }

  // Intake Code -- Works
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == true)) {
      intakeMotors.move(127);
      intakeOff = 0;
    }
  
    else if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == true)) {
      intakeMotors.move(-127);
      intakeOff = 0;
    }

    else if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) == true)) {
      intakeMotors.move(-127);
      pros::delay(500);
      intakeMotors.move(127);
    }

    else {
      intakeMotors.brake();
      if (intakeOff == 0) {
        intakeOff = 1;
      }   
    }

  // Flywheel Code -- Works
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_X) == true)) {
      flywheelMotors.move_velocity(100);
      flyWheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true)) {
      flywheelMotors.move_velocity(80);
      flyWheelOn = true;
    }
    
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == true)) {
      flywheelMotors.move_velocity(60);
      flyWheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == true)) {
      flywheelMotors.move_velocity(40);
      flyWheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) == true)) {
      flyWheelOn = false;
    }

    if (flyWheelOn == true) {
       flywheelMotors.move(127);
       flywheelOff = 0;
    }

    if (flyWheelOn == false) {
      flywheelMotors.brake();
      flywheelOff = 1;
      
    }

  // Plow Code -- Works

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true)&&(plow == 1)) {
      rightClownPiston.set_value(true);
      wrongClownPiston.set_value(true);
      plow = 0;
      waitUntil(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == false);
    }  

    if((master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true)&& (plow == 0)){
      rightClownPiston.set_value(false);
      wrongClownPiston.set_value(false);
      plow = 1;
      waitUntil(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == false);
    }

  } // End of forever loop
}