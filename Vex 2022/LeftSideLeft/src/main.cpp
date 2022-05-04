/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// FR                   motor         2               
// FL                   motor         3               
// BR                   motor         13              
// BL                   motor         21              
// BLift                motor         15              
// Conveyer             motor         18              
// ML                   motor_group   6, 8            
// LatchPneumatic       digital_out   B               
// LiftPneumantic       digital_out   D               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "autonFunctionHeader.h"
#include "driveFunctionHeader.h"

using namespace vex;

// A global instance of competition
competition Competition;
// define your global instances of motors and other devices here
inertial imu = inertial(vex::PORT16);
motor_group driveTrainLeft = motor_group(FL, BL);
motor_group driveTrainRight = motor_group(FR, BR);
smartdrive driveTrain = smartdrive(driveTrainLeft, driveTrainRight, imu, 12.5663706143591, 1, 1, distanceUnits::in, 1.0);


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

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

void autonomous(void) 
{

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  ML.setPosition(0, vex::rotationUnits (deg));
  BL.setPosition(0, vex::rotationUnits (deg));
  driveTrain.setRotation(0, vex::rotationUnits (deg));

  autonLatchOpen (false);

  smoothDrive (54, 100);

  autonLatchClose (false);

  ML.setStopping(hold);

  ML.spinToPosition(150, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  smoothDrive (-52, 100);

  driveTrain.turnToRotation (-77, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  ML.spinToPosition(500, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  BLift.setStopping(coast);

  smoothDrive (6, 100);

  BLift.spinToPosition(-1000, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  smoothDrive (-11, 100);

  BLift.spinToPosition(-500, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  smoothDrive (4, 100);

  BLift.spinToPosition(-800, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  BLift.spinToPosition(-475, vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  ML.spinToPosition(200,vex::rotationUnits (deg), 100, vex::velocityUnits (pct), true);

  autonRingLiftOn (75, true);

  wait (1500, msec);

  autonRingLiftOff ();
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

void usercontrol(void) {
  // User control code here, inside the loop
  Conveyer.setVelocity(100, percent);
  bool HToggling = false;
  bool DirToggling = false;
  bool HToggle = false;
  bool DirToggle = true;
  bool ConveyerToggle = false;
  bool ConveyerToggling = false;
  bool UpToggle = false;
  bool DownToggle = false;
  bool LatchToggle = true;
  bool LatchToggling = false;
  bool LiftToggle = false;
  bool LiftToggling = false;
  float Y;
  float Z;
  ML.setVelocity(100, percent);
  BLift.setVelocity(100, percent);
  Conveyer.setVelocity(100, percent);

  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(0, 0);
  Controller1.Screen.print("Emergency Hold: off");
  Controller1.Screen.setCursor(2, 0);
  Controller1.Screen.print("RingLift Dir: Forward");
  bool HoldToggleValue = false;
  bool DirToggleValue = false;
  while (1) {
    Y = Controller1.Axis1.position(pct);
    Z = Controller1.Axis3.position(pct);

    HToggleDrive(HToggle, HToggling); //Hold toggle
    DirToggleDrive(DirToggle, DirToggling, ConveyerToggle, UpToggle, DownToggle); //Latch toggle 
    RingLift (DirToggle, ConveyerToggle);
    Screen_Write(HToggle, DirToggle, DirToggleValue, HoldToggleValue); //Updates the display.
    DriveAlgorithm(Y, Z, driveTrainLeft, driveTrainRight); //Drive Code.
    MLLift(); //Main Lift
     //Front Lift Latch
    BLiftDrive(); //Back Lift
    Latch(LatchToggle, LatchToggling);
    LiftMove (LiftToggle, LiftToggling);
    
    

    /*
    if (Controller1.ButtonDown.pressing() && !HToggling) {
      HToggling = true;
      HToggle = !HToggle; 
      Screen_Write();
    }

    else if (!Controller1.ButtonDown.pressing())
    {
      HToggling = false;
    }

    if (HToggle == true)
    {
      FR.setStopping(hold);
      FL.setStopping(hold);
      BR.setStopping(hold);
      BL.setStopping(hold);
    }
    
    else if (HToggle == false)
    {
      FR.setStopping(coast);
      FL.setStopping(coast);
      BL.setStopping(coast);
      BR.setStopping(coast);
    }

    if (Controller1.ButtonUp.pressing() && DirToggling == false)
    {
      DirToggle = !DirToggle;
      DirToggling = true;
      Screen_Write();
    }

            else if (!Controller1.ButtonUp.pressing())
    {
      DirToggling = false;
    }

    if (Controller1.ButtonL1.pressing()) {
      ML.spin(forward);
    } else if (Controller1.ButtonL2.pressing()) {
      ML.spin(reverse);
    } else {
      ML.stop(hold);
    }

    if (Controller1.ButtonR1.pressing() && !LimitSwitchB) {
      Conveyer.spin(forward);
    } else if (Controller1.ButtonR2.pressing()) {
      Conveyer.spin(reverse);
    } 
    else if (DirToggle)
    {
      Conveyer.stop(hold);
    }
    else
    {
      Conveyer.stop(coast);
    }

    if (Controller1.ButtonX.pressing()) {
      BLift.spin(forward);
    } else if (Controller1.ButtonB.pressing()) {
      BLift.spin(reverse);
    } else {
      BLift.stop(hold);
    } */
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
