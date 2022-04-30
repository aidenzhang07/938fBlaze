void DriveAlgorithm(float Y, float Z, vex::motor_group leftDriveTrain, vex::motor_group rightDriveTrain);
void Screen_Write(bool HToggle, bool DirToggle, bool &DirToggleValue, bool &HoldToggleValue);
void HToggleDrive (bool &HToggle, bool &HToggling);
void DirToggleDrive (bool &DirToggle, bool &DirToggling, bool &ConveyerToggle, bool &UpToggle, bool &DownToggle);
void MLLift ();
void BLiftDrive ();
void RingLift (bool DirToggle, bool ConveyerToggle);
void Latch (bool &LatchToggle, bool &LatchToggling);
void LiftMove (bool &LiftToggle, bool &LiftToggling);
