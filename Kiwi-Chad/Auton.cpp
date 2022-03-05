#include "Auton.h"
#include "vex.h"

void DriveForward(double tiles){
  Drivetrain.driveFor(directionType::fwd, tiles * 24.0, distanceUnits::in);
}

void DriveBackward(double tiles){
  Drivetrain.driveFor(directionType::rev, tiles * 24.0, distanceUnits::in)
}

void TurnRight(){
  Drivetrain.turnFor(90.0, rotationUnits::deg, true);
}

void TurnLeft(){
  Drivetrain.turnFor(-90.0, rotationUnits::deg, true);
}

void ClawDown(){
  Pump.set(true);
}

void ClawUp(){
  Pump.set(false);
}

/*
if (Controller1.ButtonR2.pressing()){
    Pump.set(true);
  }
  else if (Controller1.ButtonR1.pressing()){
    Pump.set(false);
  }
  */