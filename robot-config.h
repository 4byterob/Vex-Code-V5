using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor L_Down;
extern motor L_Up;
extern motor R_Down;
extern motor R_Up;
extern motor L_ArmSpin;
extern motor R_ArmSpin;
extern motor ClawSpin;
extern motor_group GroupTest;
extern digital_out Pump;
extern motor Tail;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );