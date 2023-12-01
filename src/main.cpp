#include "main.h"
#include "initialize.h"

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
  pros::ADIDigitalOut rightClownPiston(2,false);
  rightClownPiston.set_value(false);
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

  pros::ADIDigitalIn AutonSelect (6);
  Inert.reset();


  //1 is near, 2 is far

  /* if (AutonSelect.get_value()<2400){
    autonSelecto_thingy = 1;
  } else {
    autonSelecto_thingy = 2;
  } */

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
  
  //1 is near, 2 is far
  int rotation;

  pros::Distance Distance(7);
  pros::ADIDigitalIn elevationButton(5);

  pros::ADIDigitalOut rightClownPiston(2,false);
  pros::ADIDigitalOut wrongClownPiston(1,false);
  
  allWheels.move_velocity(100);
  allWheels.brake();

/*

  // near auton
  
  Inert.tare();
  
  allWheels.set_brake_modes(MOTOR_BRAKE_COAST);

 //driving to the goal to drop off the match
  allWheels.move(-100);
  pros::delay(250);
  allWheels.brake();
  pros::delay(750);
  allWheels.move(-100);
  pros::delay(750);
  allWheels.brake();
  pros::delay(200);

 //making ourselves flat against the goal 
  rightWheels.move(-100);
  pros::delay(600);
  allWheels.brake();
  pros::delay(200);

 //driving to the match load zone and positioning to pick up the triball 
  allWheels.move(100);
  pros::delay(200);
  allWheels.brake();
  pros::delay(200);
  
  //turning to be parallel with the match load zone
  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=335)&&(Inert.get_heading()<=345));
  allWheels.brake();
  pros::delay(200);

  //lining ourselves up with the triball along that parallel
  allWheels.move(95); 
  waitUntil((Distance.get() >= 190) && (Distance.get() <= 240));
  allWheels.brake();
  pros::delay(300);

  //Turning to be perpendicular to the match load zone
  rightWheels.move(-50);
  leftWheels.move(50);
  waitUntil((Inert.get_heading()>=60)&&(Inert.get_heading()<=90));

  allWheels.move(50);
  pros::delay(125);
  allWheels.brake();

  //driving in to get the triball
  pros::delay(100);
  allWheels.move(75);
  armIntake.move(100);
  pros::delay(450);
  allWheels.move(-45);
  pros::delay(250);
  allWheels.brake();

  //picking up triball
  arm.move(50);

  //waitUntil(intakeButton.get_value() == true); <-- make an or statement in the future
  pros::delay(2000);


  // achieved triball from zone and picking it up
  arm.brake();
  pros::delay(300);
  armIntake.brake();
  pros::delay(100);
  arm.move(-100);
  waitUntil(intakeSwitch.get_value() == true);
  arm.brake();

  pros::delay(200);

  // DON'T TOUCH TOP CODE IT WORKS




  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=340)&&(Inert.get_heading()<=350));
  allWheels.brake();



  allWheels.move(100);
  pros::delay(500);
  allWheels.brake();
  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=293)&&(Inert.get_heading()<=298));
  allWheels.brake();
  pros::delay(300);

  allWheels.move(50);

  // removing the triball
  pros::delay(100);
  arm.move(100);
  armIntake.move(-100);
  pros::delay(400);
  arm.brake();
  armIntake.brake();
  pros::delay(200);
  arm.move(-100);
  waitUntil(intakeSwitch.get_value() == true);
  arm.brake();

  // moving to the elevation bar
  waitUntil(elevationButton.get_value() == true);
  allWheels.brake();







/*


/*
// far auton

  Inert.tare();
  
    allWheels.set_brake_modes(MOTOR_BRAKE_COAST);
  
  // move to the center of the field
  allWheels.move(55);
  waitUntil((Distance.get() >= 1050) && (Distance.get() <= 1100));
  allWheels.brake();
  pros::delay(200);

  // back up a little bit
  allWheels.move(-50);
  waitUntil((Distance.get() >= 950) && (Distance.get() <= 1000));
  allWheels.brake();

  // turn to the middle bar, at an angle
  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=325)&&(Inert.get_heading()<=335));
  allWheels.brake();
  pros::delay(100);

  // move to the middle bar, at an angle
  allWheels.move(100);
  pros::delay(600);
  allWheels.brake();
  pros::delay(100);

  // turn toward the goal
  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=285)&&(Inert.get_heading()<=295));
  allWheels.brake();
  pros::delay(100);

  // activate the piston
  rightClownPiston.set_value(true);
  pros::delay(100);

  // push the triballs to the goal
  allWheels.move(-100);
  pros::delay(750);
  allWheels.brake();
  pros::delay(200);

  // move a little more toward the goal for alignment
  allWheels.move(-100);
  pros::delay(200);
  allWheels.brake();
  pros::delay(100);

  // deactivate the piston
  rightClownPiston.set_value(false);
  pros::delay(100);

  // back up a little bit
  allWheels.move(100);
  pros::delay(150);
  allWheels.brake();
  pros::delay(100);


  // turn toward the elevation pole
  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=230)&&(Inert.get_heading()<=240));
  allWheels.brake();
  pros::delay(100);

  // move to the elevation pole
  allWheels.move(100);
  pros::delay(600);
  allWheels.brake();
  pros::delay(100);

  // move the arm into the elevation pole
  arm.move(50);
  pros::delay(600);
  arm.brake();
*/

  //Skills Auton

  allWheels.set_brake_modes(MOTOR_BRAKE_HOLD);
  Inert.tare();
  pros::delay(200);
  leftWheels.move(50);
  waitUntil((Inert.get_heading()>20)&&(Inert.get_heading()<25));
  allWheels.brake();
  arm.move(100);
  waitUntil(intakeButton.get_value()==true);
  flywheelMotors.move(60);
  pros::delay(1000);
  flywheelMotors.brake();
  arm.move(-100); 
  rightWheels.move(-50);
  waitUntil(Inert.get_heading()>43);
  allWheels.brake();
  waitUntil(intakeSwitch.get_value()==true);
  arm.brake();
  allWheels.move(-100);
  pros::delay(1000);
  leftWheels.move(50);
  rightWheels.move(-50);
  waitUntil((Inert.get_heading()>65)&&(Inert.get_heading()<90));
  allWheels.brake();

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

	pros::Motor intakeFeed(13, 0);

  pros::ADIDigitalOut rightClownPiston(2,false);
  pros::ADIDigitalOut wrongClownPiston(1,false);

  //Port #'s
  //1,2,3,4,5,6,7,8
  //A,B,C,D,E,F,G,H
  pros::ADIDigitalOut shieldPiston(3);
  pros::ADIDigitalOut elevationPiston(7);
  allWheels.set_brake_modes(MOTOR_BRAKE_COAST);

  int testaeai0jfoijfewahu99 = 0;

  int elevation = 1;
  int plow = 1;
  bool flywheelOn = false;
  int intakeOff = 1;
  int drvtrDZ;
  int armDZ;
  int armUD;
  int drvtrFB;
  int drvtrLR;
  int minDeg;
  int maxDeg;

  allWheels.move_velocity(100);

  while (1==1) {


  //Drivetrain Code -- [Working | Final Keybinds]
   //Defines the values for the left and right joysticks, along with 
   //  a deadzone where the position of the joysticks does nothing
   //These are put inside of the while loop so that the code can 
   //  adapt to movements mid-match
    drvtrFB = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    drvtrLR = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    drvtrDZ = 10;
   //Makes the motors move by taking the FB and LR values and adding 
   //  or subtracting them for one another
    
    if((abs(drvtrFB) > drvtrDZ) || (abs(drvtrLR) > drvtrDZ)) {
      // ^^ Checks to see if either joystick has moved out of the deadzone
      rightWheels.move((drvtrFB-drvtrLR));
      leftWheels.move((drvtrFB+drvtrLR));

    } else {
      rightWheels.brake();
      leftWheels.brake();
    }     

    if((abs(drvtrFB) > drvtrDZ) || (abs(drvtrLR) > drvtrDZ)) {
      // ^^ Checks to see if either joystick has moved out of the deadzone
      rightWheels.move((drvtrFB - drvtrLR));
      leftWheels.move((drvtrFB + drvtrLR));
      
    } else {
      rightWheels.brake();
      leftWheels.brake();
    }


  // Flywheel Code -- [Working | Final Keybinds]
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_X) == true)) {
      flywheelMotors.move_velocity(100);
      flywheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true)) {
      flywheelMotors.move_velocity(75);
      flywheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_B) == true)) {
      flywheelMotors.move_velocity(60);
      flywheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) == true)) {
      flywheelOn = false;
    }

    if (flywheelOn == true) {
       flywheelMotors.move(127);
    }

    if (flywheelOn == false) {
      flywheelMotors.brake();
    }

  // Feed Code [Working || Final Keybinds]
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == true) {
      intakeFeed.move(127);

    } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) == true) {
      intakeFeed.move(-127);

    } else {
      intakeFeed.brake();
    }

  // Plow Code -- [Working || Final Keybinds]
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true) && (plow == 1)) {
      rightClownPiston.set_value(true);
      wrongClownPiston.set_value(true);
      plow = 0;
      waitUntil(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == false);
    }  

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true) && (plow == 0)){
      rightClownPiston.set_value(false);
      wrongClownPiston.set_value(false);
      plow = 1;
      waitUntil(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == false);
    }

  //Shield Code
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == true){
      shieldPiston.set_value(true);

    } else {
      shieldPiston.set_value(false);
    }

  //Intake Code (Partner Controller)
    armUD = partner.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    armDZ = 10;
    minDeg = 0;
    maxDeg = 165;

    if ((armUD > armDZ) && (intakeButton.get_value() == false)) {
      arm.move(armUD);
    } 

    else if ((armUD < (-1 * armDZ)) && (intakeSwitch.get_value() == false)) {
      arm.move(armUD);
    }

    else if ((partner.get_digital(pros::E_CONTROLLER_DIGITAL_Y) == true)) {
      armIntake.move(127);
      partner.print(0, 0, "It works");
    }

    else if ((partner.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true)) {
      armIntake.move(-127);
      partner.print(0, 0, "Oit Waakss");
    }


/*
  // doesn't work
    else if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) == true) {
      do {
        arm.move(127);
      } while (intakeButton.get_value() == false);
      arm.move_absolute(maxDeg, 600);
      armIntake.move(-127);
      pros::delay(250);
      armIntake.brake();
    }
*/

    else {
      arm.brake();
      armIntake.brake();
    }

    if (partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == true) {

      if(elevation == 1) {
        elevationPiston.set_value(true);
        elevation = 2;
        waitUntil(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == false);

      } else if (elevation == 2) {
        elevationPiston.set_value(false); 
        elevation = 1;
        waitUntil(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == false);
      }
    } 

  } //end of forever code
}