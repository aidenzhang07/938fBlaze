#include "vex.h"


void DriveAlgorithm(float Y, float Z, vex::motor_group leftDriveTrain, vex::motor_group rightDriveTrain) {
  leftDriveTrain.setVelocity(1.25 * (Z + Y), percent);
  rightDriveTrain.setVelocity(1.25 * (Z - Y), percent);
  FL.spin(forward);
  FR.spin(forward);
  BL.spin(forward);
  BR.spin(forward);
}

void Screen_Write(bool HToggle, bool DirToggle, bool &DirToggleValue, bool &HoldToggleValue)
{

  if(HToggle == true && !HoldToggleValue)
  {
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.clearLine(1);
    HoldToggleValue = true;
    Controller1.Screen.print("Emergency Hold: on");
  }
  if(HToggle == false && HoldToggleValue)
  {
    Controller1.Screen.setCursor(0, 0);
    Controller1.Screen.clearLine(1);
    HoldToggleValue = false;
    Controller1.Screen.print("Emergency Hold: off");
  }
  if(DirToggle == true && !DirToggleValue)
  {
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.clearLine(2);
    DirToggleValue = true;
    Controller1.Screen.print("RingLift Dir: Forward");
  }
  if(DirToggle == false && DirToggleValue)
  {
    Controller1.Screen.setCursor(2, 0);
    Controller1.Screen.clearLine(2);
    DirToggleValue = false;
    Controller1.Screen.print("RingLift Dir: Backward");
  }
}


void HToggleDrive (bool &HToggle, bool &HToggling){
  if (Controller1.ButtonLeft.pressing() && !HToggling) {
    HToggling = true;
    HToggle = !HToggle;
  }

  else if (!Controller1.ButtonLeft.pressing())
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
}

void DirToggleDrive (bool &DirToggle, bool &DirToggling, bool &ConveyerToggle, bool &UpToggle, bool &DownToggle){
  if (Controller1.ButtonUp.pressing() && DirToggling == false && UpToggle == false)
  {
    DirToggle = true;
    ConveyerToggle = true;
    DirToggling = true;
    UpToggle = true;
    DownToggle = false;
    //Controller1.Screen.clearScreen();
  }
  else if (Controller1.ButtonUp.pressing() && DirToggling == false)
  {
    ConveyerToggle = false;
    DirToggling = true;
    UpToggle = false;
  }

  if (Controller1.ButtonDown.pressing() && DirToggling == false && DownToggle == false)
  {
    DirToggle = false;
    ConveyerToggle = true;
    DirToggling = true;
    DownToggle = true;
    UpToggle = false;
  }
  else if (Controller1.ButtonDown.pressing() && DirToggling == false)
  {
    ConveyerToggle = false;
    DirToggling = true;
    DownToggle = false;
  }
  if (!Controller1.ButtonDown.pressing() && !Controller1.ButtonUp.pressing())
  {
    DirToggling = false;
  }
}

void MLLift (){
  if (Controller1.ButtonL1.pressing()) {
    ML.spin(forward);
  } else if (Controller1.ButtonL2.pressing()) {
    ML.spin(reverse);
  } else{
    ML.stop(hold);
  }
}

void RingLift (bool DirToggle, bool ConveyerToggle){

  if (ConveyerToggle && DirToggle) {
    Conveyer.spin(forward);
  } else if (ConveyerToggle && !DirToggle) {
    Conveyer.spin(reverse);
  } else
  {
    Conveyer.stop(coast);
  }
}
void BLiftDrive (){
  if (Controller1.ButtonX.pressing()) {
    BLift.spin(forward);
  } else if (Controller1.ButtonB.pressing()) {
    BLift.spin(reverse);
  } else {
    BLift.stop(hold);
  }
}

void Latch (bool &LatchToggle, bool &LatchToggling) 
{
  if (Controller1.ButtonR1.pressing() && LatchToggle == true && LatchToggling == false)
  {
    LatchPneumatic = true;
    LatchToggle = false;
    LatchToggling = true;
  } else if (Controller1.ButtonR2.pressing() && LatchToggle == false && LatchToggling == false)
  {
    LatchPneumatic = false;
    LatchToggle = true;
    LatchToggling = true;
  } else if (Controller1.ButtonR1.pressing() == false && Controller1.ButtonR2.pressing() == false)
  {
    LatchToggling = false;
  }
}

void LiftMove (bool &LiftToggle, bool &LiftToggling)
{
  if (Controller1.ButtonRight.pressing() && LiftToggle ==  false && LiftToggling == false)
  {
    LiftPneumantic = true;
    LiftToggle = true;
    LiftToggling = true;
  }
  else if (Controller1.ButtonRight.pressing() && LiftToggle == true && LiftToggling == false)
  {
    LiftPneumantic = false;
    LiftToggle = false;
    LiftToggling = true;
  }
  else if (Controller1.ButtonRight.pressing() == false)
  {
    LiftToggling = false;
  }
}