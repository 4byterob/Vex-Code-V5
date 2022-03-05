/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Tue Mar 01 2022                                           */
/*    Description:  Exactly the same project as the last, just clearner code. */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    11, 12, 19, 20  
// Arms                 motor_group   1, 10           
// Pump                 digital_out   A               
// TestMotor            motor         16              
// Tail                 motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "drivetrain.h"
#include "Auton.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

int AutonType = 1;

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  if (AutonType == 1){
    DriveForward();
    ClawDown();
    DriveBackward();

    TurnLeft();
    ArmsUp(1.0);
    DriveForward();

    ClawDown();
    TurnRight();
    ArmsDown(1.0);
    
    DriveForward(2.0);
    ClawDown();
    DriveBackward(2.0);
  }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void PumpAction(){
  if (Controller1.ButtonR2.pressing()){
    Pump.set(true);
  }
  else if (Controller1.ButtonR1.pressing()){
    Pump.set(false);
  }
}

void usercontrol(void) {
  // User control code here, inside the loop
  DriveTrain dTrain;
  Brain.Screen.print(dTrain.ReturnVelocity());

  Pump.set(false);
  
  while (1) {
    PumpAction();   // Pneumatic Control

    // Basic Drive
    double hVelocity = Controller1.Axis3.position(percent);
    double vVelocity = Controller1.Axis4.position(percent);

    dTrain.Drive(hVelocity, vVelocity);
    
    // Basic Arm Movement
    double armVelocity = Controller1.Axis1.position(percent);
    Arms.setVelocity(armVelocity, percentUnits::pct);
    Arms.spin(directionType::fwd);

    //Arms.spin(directionType::fwd, armVelocity, velocityUnits::pct);

    if (Controller1.ButtonL1.pressing()){
      Tail.setVelocity(100.0, pct);
      Tail.spin(forward);
    }
    else{
      Tail.setVelocity(0.0, pct);
    }
    if (Controller1.ButtonL2.pressing()){
      Tail.setVelocity(100.0, pct);
      Tail.spin(forward);
    }
    else{
      Tail.setVelocity(0.0, pct);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
