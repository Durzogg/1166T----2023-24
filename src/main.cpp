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
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	
	pros::Motor frontLeft(1);
	pros::Motor frontRight(2);

	pros::Motor backLeft(3); // I don't know if this is correct, will check next time the robot is tested
	pros::Motor backRight(4);

	pros::Motor leftFlywheel(5);
	pros::Motor rightFlywheel(6);

	pros::Motor leftIntake(11); // I also don't know if this is correct, will check next time the robot is tested
	pros::Motor rightIntake(12);

	pros::Motor_Group flywheelMotors({leftFlywheel, rightFlywheel});
	pros::Motor_Group intakeMotors({leftIntake, rightIntake});

	pros::ADIDigitalOut elevationPiston(); // whatever port we are using for the elevation pneumatic
	pros::ADIDigitalOut leftPlowPiston(); // whatever port we are using for the left plow piston
	pros::ADIDigitalOut rightPlowPiston(); // whatever port we are using for the right plow piston

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
void competition_initialize() {}

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
void autonomous() {}

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

	while(true){
		
		pros::delay(5);
	}
}
	
	/*
  int pnue = 1;

  int drvtrFB = 1;
  int drvtrLR = 1;
  int drvtrDZ = 10;
  int elevationOff = 1;
  int intakeOff = 1;
  int flywheelOff = 1;
  bool flyWheelOn = false;
  
  frontRight.setMaxTorque(100,percent);
  backRight.setMaxTorque(100,percent);
  frontLeft.setMaxTorque(100,percent);
  backLeft.setMaxTorque(100,percent);

  // Start of Elevation Code
  while (1) {
    drvtrFB = 1;
    drvtrLR = 1;
    // Checks for button pressing and if the Fixed Pneumatic code hasn't been
    // activated
    if ((Controller1.ButtonR1.pressing() == true) && (pnue != 2)) {
      elePnu.set(true);
      Controller1.Screen.print("ElevationPnu = true");
      Controller1.Screen.newLine();
      elevationOff = 0;
    }  else if(pnue == 1){
      elePnu.set(false);
      if (elevationOff == 0) {
        Controller1.Screen.print("ElevationPnu = false");
        Controller1.Screen.newLine();
        elevationOff = 1;
      }
    }
    // Checks for B button being pressed and lockes the code to keep the
    // pneumatic fixed in place
    if ((Controller1.ButtonR2.pressing() == true) || (pnue == 2)) {
      elePnu.set(true);
      Controller1.Screen.print("ElevationPnu = Fixed");
      Controller1.Screen.newLine();
      pnue = 2;
    }

    if ((abs(Controller1.Axis3.position(percent))>drvtrDZ) || (abs(Controller1.Axis1.position(percent))>drvtrDZ)){

      speedRightSide(1.2*(Controller1.Axis3.position(percent)-(Controller1.Axis1.position(percent))));
      speedLeftSide(1.2*(Controller1.Axis3.position(percent)+(Controller1.Axis1.position(percent))));

      spinRightSide();
      spinLeftSide();
    }else{
      cease();
    }


    wait(0.1,sec);

  

//clockwise decending


    // start of intake code
    intakeVelocity(100);
    if ((Controller1.ButtonRight.pressing() == true)) {
      Intake_Motors.spin(forward);
      Controller1.Screen.print("Intake_Motors = on");
      Controller1.Screen.newLine();
      intakeOff = 0;
    }

    else if ((Controller1.ButtonLeft.pressing() == true)) {
      Intake_Motors.spin(reverse);
      Controller1.Screen.print("Intake_Motors = on");
      Controller1.Screen.newLine();
      intakeOff = 0;
    }

    else {
      Intake_Motors.stop();
      if (intakeOff == 0) {
        Controller1.Screen.print("Intake_Motors = off");
        Controller1.Screen.newLine();
        intakeOff = 1;
      }   
    }

    // end of intake code

    // start of flywheel code
    if ((Controller1.ButtonX.pressing() == true)) {
      flyWheelMotors.setVelocity(100,percent);
      flyWheelOn = true;
    }

    if ((Controller1.ButtonY.pressing() == true)) {
      flyWheelMotors.setVelocity(40,percent);
      flyWheelOn = true;
    }

    if ((Controller1.ButtonB.pressing() == true)) {
      flyWheelMotors.setVelocity(60,percent);
      flyWheelOn = true;
    }

    if ((Controller1.ButtonA.pressing() == true)) {
      flyWheelMotors.setVelocity(80,percent);
      flyWheelOn = true;
    }

    if ((Controller1.ButtonB.pressing() == true)) {
      flyWheelMotors.setVelocity(60,percent);
      flyWheelOn = true;
    }

    if ((Controller1.ButtonDown.pressing() == true)) {
      flyWheelOn = false;

    }
    if (flyWheelOn == true) {
       flyWheelMotors.spin();
       Controller1.Screen.print("flyWheelMotors = on");
       Controller1.Screen.newLine();
       flywheelOff = 0;
    }
    if (flyWheelOn == false) {
      flyWheelMotors.stop();
      Controller1.Screen.print("flyWheelMotors = off");
      Controller1.Screen.newLine();
      flywheelOff = 1;
      
    }
   // end of flywheel code
  }
*/
