#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor L_Down = motor(PORT12, ratio6_1, true);
motor L_Up = motor(PORT11, ratio6_1, true);
motor R_Down = motor(PORT19, ratio6_1, false);
motor R_Up = motor(PORT20, ratio6_1, false);
motor L_ArmSpin = motor(PORT1, ratio36_1, false);
motor R_ArmSpin = motor(PORT10, ratio36_1, true);
motor ClawSpin = motor(PORT15, ratio36_1, false);
motor GroupTestMotorA = motor(PORT4, ratio18_1, false);
motor GroupTestMotorB = motor(PORT5, ratio18_1, false);
motor_group GroupTest = motor_group(GroupTestMotorA, GroupTestMotorB);
digital_out Pump = digital_out(Brain.ThreeWirePort.A);
motor Tail = motor(PORT18, ratio36_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}