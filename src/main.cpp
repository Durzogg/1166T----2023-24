#include "main.h"
#include "init.h"

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
  pros::Imu Inert(9);
  pros::ADIDigitalIn AutonSelect (6);
  Inert.reset();
  //1 is near, 2 is far

  /* if (AutonSelect.get_value()<2400){
    autonSelecto_thingy = 1;
  } else {
    autonSelecto_thingy = 2;
  } */
  autonSelecto_thingy = 1;

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

  pros::Imu Inert(9);
  pros::Motor frontLeft(1,0);
	pros::Motor backLeft(4,0);
  pros::Motor arm(11, 0);
  pros::Motor armIntake(20, 0);
  pros::Motor_Group leftWheels({frontLeft, backLeft});
  leftWheels.move_velocity(100);
  pros::Motor frontRight(2,1);
	pros::Motor backRight(3,1);
  pros::Motor_Group rightWheels({frontRight, backRight});
  rightWheels.move_velocity(100);
  pros::Motor_Group allWheels({frontRight, backRight, frontLeft, backLeft});


  if(autonSelecto_thingy == 1) { //near auton

  Inert.tare();

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
  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=335)&&(Inert.get_heading()<=345));
  allWheels.brake();
  pros::delay(200);
  allWheels.move(127);
  pros::delay(300);
  allWheels.brake();
  pros::delay(300);
  rightWheels.move(-50);
  leftWheels.move(50);
  waitUntil((Inert.get_heading()>=60)&&(Inert.get_heading()<=90));
  allWheels.brake();

  //driving in to get the triball
  pros::delay(100);
  allWheels.move(75);
  armIntake.move(100);
  pros::delay(450);
  allWheels.move(-45);
  pros::delay(300);
  allWheels.brake();

  //picking up triball
  arm.move(60);

  //waitUntil(intakeButton.get_value() == true); <-- make an or statement in the future
  pros::delay(1500);


  //acheived triball from zone and picking it up
  arm.brake();
  pros::delay(300);
  armIntake.brake();
  pros::delay(100);
  arm.move(-100);
  waitUntil(intakeSwitch.get_value() == true);
  arm.brake();

  pros::delay(200);

  rightWheels.move(50);
  leftWheels.move(-50);
  waitUntil((Inert.get_heading()>=335)&&(Inert.get_heading()<=345));
  allWheels.brake();

  //DONT TOUCH TO TOP CODE IT WORKS (once)
  //TEST FIRST BEFORE MODIFYING


  } else if (autonSelecto_thingy == 2) { // far auton

  Inert.tare();

 //driving to the goal to drop off the match
  allWheels.move(-100);
  pros::delay(250);
  allWheels.brake();
  pros::delay(500);
  allWheels.move(-100);
  pros::delay(750);
  allWheels.brake();
  pros::delay(200);

 //making ourselves flat against the goal 
  rightWheels.move(-100);
  pros::delay(600);
  allWheels.brake();
  pros::delay(200);
  // Inert.tare();
  }
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
  pros::Controller partner (pros::E_CONTROLLER_PARTNER);

	pros::Motor frontLeft(1,0);
	pros::Motor backLeft(4,0);
  pros::Motor_Group leftWheels({frontLeft, backLeft});

  pros::Motor frontRight(2,1);
	pros::Motor backRight(3,1);
  pros::Motor_Group rightWheels({frontRight, backRight});
  
  pros::Motor_Group allWheels({frontRight, backRight, frontLeft, backLeft});

  pros::Motor leftFlywheel(5, 1);
	pros::Motor rightFlywheel(6, 0);
	pros::Motor_Group flywheelMotors({leftFlywheel, rightFlywheel});

	pros::Motor intakeFeed(13, 0);
  pros::Motor armIntake(20, 0);
  pros::Motor arm(11, 0);

  //Port #'s
  //1,2,3,4,5,6,7,8
  //A,B,C,D,E,F,G,H
  pros::ADIDigitalOut shieldPiston(3,false);
	pros::ADIDigitalOut elevationPiston(6,false);

	pros::ADIDigitalOut rightClownPiston(2,false);
	pros::ADIDigitalOut wrongClownPiston(1,false);

  int elevation = 1;
  int plow = 1;
  bool flyWheelOn = false;
  int intakeOff = 1;
  int drvtrDZ;
  int armDZ;
  int armUD;
  int drvtrFB;
  int drvtrLR;
  int minDeg;
  int maxDeg;

  elevationPiston.set_value(false);
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
    
        if((abs(drvtrFB)>drvtrDZ)||(abs(drvtrLR)>drvtrDZ)) {
          // ^^ Checks to see if either joystick has moved out of the deadzone
          rightWheels.move((drvtrFB-drvtrLR));
          leftWheels.move((drvtrFB+drvtrLR));
        } else {
          rightWheels.brake();
          leftWheels.brake();
        }     

        if((abs(drvtrFB)>drvtrDZ)||(abs(drvtrLR)>drvtrDZ)) {
          // ^^ Checks to see if either joystick has moved out of the deadzone
          rightWheels.move((drvtrFB-drvtrLR));
          leftWheels.move((drvtrFB+drvtrLR));
      }else{
        rightWheels.brake();
        leftWheels.brake();
    }

    }

  // Flywheel Code -- [Working | Final Keybinds]
    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_X) == true)) {
      flywheelMotors.move_velocity(100);
      flyWheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_A) == true)) {
      flywheelMotors.move_velocity(75);
      flyWheelOn = true;
    }

    if ((master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN) == true)) {
      flyWheelOn = false;
    }

    if (flyWheelOn == true) {
       flywheelMotors.move(127);
    }

    if (flyWheelOn == false) {
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
      if(elevation = 1){
        elevationPiston.set_value(true);
        elevation = 2;
        waitUntil(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == false);
      } else if(elevation = 2){
        elevationPiston.set_value(false); 
        elevation = 1;
        waitUntil(partner.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == false);
      }
    } 

  } //end of forever code
