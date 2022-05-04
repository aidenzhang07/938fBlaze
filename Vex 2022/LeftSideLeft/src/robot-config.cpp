#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor FR = motor(PORT2, ratio18_1, true);
motor FL = motor(PORT3, ratio18_1, false);
motor BR = motor(PORT13, ratio18_1, true);
motor BL = motor(PORT21, ratio18_1, false);
motor BLift = motor(PORT15, ratio18_1, false);
motor Conveyer = motor(PORT18, ratio18_1, true);
motor MLMotorA = motor(PORT6, ratio36_1, false);
motor MLMotorB = motor(PORT8, ratio36_1, true);
motor_group ML = motor_group(MLMotorA, MLMotorB);
digital_out LatchPneumatic = digital_out(Brain.ThreeWirePort.B);
digital_out LiftPneumantic = digital_out(Brain.ThreeWirePort.D);

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