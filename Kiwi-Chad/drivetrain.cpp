#include "drivetrain.h"
#include "vex.h"

using namespace vex;

DriveTrain::DriveTrain()
{
  velocity = 1.0;
}

double DriveTrain::ReturnVelocity()  { return velocity; }
void DriveTrain::IncreaseVelocity()  { velocity += 0.1; SetVelocity(velocity); }
void DriveTrain::DecreaseVelocity()  { velocity -= 0.1; SetVelocity(velocity); }
void DriveTrain::SetVelocity(double newVel)
{
  velocity = newVel;
  Drivetrain.setDriveVelocity(velocity, percent);
}

void DriveTrain::Drive(double hVel, double vVel)
{
  Drivetrain.setDriveVelocity(vVel, percentUnits::pct);
  Drivetrain.setTurnVelocity(hVel, percentUnits::pct);

  Drivetrain.drive(directionType::fwd);
  Drivetrain.turn(turnType::right);

  /*
  Drivetrain.drive(directionType::fwd, vVel, velocityUnits::pct);
  Drivetrain.turn(turnType::right, hVel, velocityUnits::pct);
  */
}