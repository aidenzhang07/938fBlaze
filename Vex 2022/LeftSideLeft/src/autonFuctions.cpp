#include "vex.h"

//const float wheelDiameter = 4;
//const float wheelCircumference = wheelDiameter * 3.1416;
//const float inchesPerDegree = wheelCircumference/360;
//const float driveGearRatio = 0.7142857;
//const float turningDiameter = 17.5;
//const float turningRatio = turningDiameter / wheelDiameter;

/*void autonSmoothTurn(float turnDegrees, float volocityPct, bool doWaitForFinished, bool resetIMU = true);
{
  driveTrain.turnToRotation(turnDegrees, deg, volocityPct, velocityUnits::pct, doWaitForFinished);
}*/

void autonLatchOpen(bool doWaitForFinished)
{
  LatchPneumatic = true;

  if (doWaitForFinished)
  {
    wait(300, msec);
  }
}

void autonLatchClose(bool doWaitForFinished)
{
  LatchPneumatic= false;

  if (doWaitForFinished)
  {
    wait(300, msec);
  }
}

void autonRaiseRingLift(bool doWaitForFinished)
{
  LiftPneumantic = true;

  if (doWaitForFinished)
  {
    wait(2000, msec);
  }
}

void autonLowerRingLift(bool doWaitForFinished)
{
  LiftPneumantic = false;

  if (doWaitForFinished)
  {
    wait(2000, msec);
  }
}

//Turns the ring lift on and lets it run wile the program does other stuff.
//velocityPct is the persentage of the maximum speed of the motor that you want the ring lift to run at.
void autonRingLiftOn(int velocityPct, bool ringLiftForward)
{
  if (ringLiftForward == true)
  {
    Conveyer.setVelocity(velocityPct, pct);
    Conveyer.spin(forward);
  }
  if (ringLiftForward == false)
  {
    Conveyer.setVelocity(velocityPct, pct);
    Conveyer.spin(reverse);
  }
}

void autonRingLiftOff()
{
  Conveyer.stop(coast);
}

void smoothDrive(float inches, float startSpeed)
{
  float numberOfRevsAtStart = FR.rotation(rotationUnits::rev);
  float revolutionsDriven = FR.rotation(rotationUnits::rev) - numberOfRevsAtStart;
  float whenStartSlowdown = 1;
  float minSpeed = 5;
  float currentSpeed = startSpeed;
  float fudgeNumber = 0.97569444444444444444444444444444;

  int direction = 1;
  if (inches < 0)
  {
    direction = -1;
  }

  inches = fabs(inches) * fudgeNumber;
  float targetRevolutions = inches / 12.566370614359172953850573533118;

  if (targetRevolutions < 12.566370614359172953850573533118)
  {
    whenStartSlowdown = 0;
  }

  FL.spin(forward);
  BL.spin(forward);
  FR.spin(forward);
  BR.spin(forward);

  while (true)
  {
    revolutionsDriven = FR.rotation(rotationUnits::rev) - numberOfRevsAtStart;
    if (fabs(revolutionsDriven) >= fabs(targetRevolutions))
      break; // ====>

    currentSpeed = startSpeed;

    //Calculates the speed that the motors have to turn at to slow to a stop.
    if (fabs(revolutionsDriven) > fabs(targetRevolutions) - whenStartSlowdown)
    {
      currentSpeed = minSpeed + ((fabs(targetRevolutions) - fabs(revolutionsDriven)) / whenStartSlowdown) * (startSpeed - minSpeed);
    }

    FR.setVelocity(direction * currentSpeed, percent);
    FL.setVelocity(direction * currentSpeed, percent);
    BR.setVelocity(direction * currentSpeed, percent);
    BL.setVelocity(direction * currentSpeed, percent);

    //Short pause before setting speed again
    wait(10, msec);
  }

  // Uncomment this if stop() doesn't seem to stop
  //
  // FR.setVelocity(direction * -10, percent);
  // FL.setVelocity(direction * -10, percent);
  // BR.setVelocity(direction * -10, percent);
  // BL.setVelocity(direction * -10, percent);
  // wait(20, msec);

  FR.stop(brake);
  FL.stop(brake);
  BR.stop(brake);
  BL.stop(brake);
}

void driving(float inches, float turnVelocity, bool doWaitForFinished)
{
  float numberOfRevsAtStart = FR.rotation(rotationUnits::rev);
  float revolutionsDriven = FR.rotation(rotationUnits::rev) - numberOfRevsAtStart;
  float fudgeNumber = 0.97569444444444444444444444444444;
  inches = fabs(inches) * fudgeNumber;
  float targetRevolutions = inches / 12.566370614359172953850573533118;

  FR.setStopping(brake);
  FL.setStopping(brake);
  BR.setStopping(brake);
  BL.setStopping(brake);

  FR.spinFor(targetRevolutions, vex::rotationUnits (rev), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
  FL.spinFor(targetRevolutions, vex::rotationUnits (rev), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
  BR.spinFor(targetRevolutions, vex::rotationUnits (rev), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
  BL.spinFor(targetRevolutions, vex::rotationUnits (rev), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
}


// sides = 0 for both sides active (tractor turn), 1 = left active, 2 = right active 
void autoTurn (float turnDegrees, int velocityPct, char sides, inertial& imu)
{

  imu.resetRotation();

  int turnDirection = 1;
  if (turnDegrees  < 0)
  {
    turnDirection = -1;
  }

  if (sides == 'b' || sides == 'B')
  {
    FL.spin(forward);
    BL.spin(forward);
    FR.spin(forward);
    BR.spin(forward);
    FR.setVelocity(turnDirection * velocityPct * -1, percent);
    FL.setVelocity(turnDirection * velocityPct, percent);
    BR.setVelocity(turnDirection * velocityPct * -1, percent);
    BL.setVelocity(turnDirection * velocityPct, percent);
  } 
    
  else if (sides == 'l' || sides == 'L')
  {
    FL.spin(forward);
    BL.spin(forward);
    FL.setVelocity(turnDirection * velocityPct, percent);
    BL.setVelocity(turnDirection * velocityPct, percent);
  } 
    
  else if (sides == 'r' || sides == 'R')
  {
    FR.spin(forward);
    BR.spin(forward);
    FR.setVelocity(turnDirection * velocityPct * -1, percent);
    BR.setVelocity(turnDirection * velocityPct * -1, percent);
  }

  while (fabs(imu.rotation(rotationUnits::deg)) < fabs(turnDegrees))
  {
    Brain.Screen.print(imu.rotation(rotationUnits::deg));
    Brain.Screen.newLine();
  }

  FR.stop(brake);
  FL.stop(brake);
  BR.stop(brake);
  BL.stop(brake);
}

void autoFrontLift (float liftDegrees, int liftVelocity, bool doWaitForFinished, bool doHold, int goTopOrBottom = 0)
{
  if (goTopOrBottom == 1)
  {
    ML.spinFor(600, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (goTopOrBottom == 2)
  {
    ML.spinFor(-600, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else
  {
    ML.spinFor(liftDegrees, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  if (doHold)
  {
    ML.stop(hold);
  }
}

void autoBackLift (float liftDegrees, int liftVelocity, bool doWaitForFinished, bool doHold, int toTopOrBottom = 0)
{

  if (toTopOrBottom == 1)
  {
    BLift.spinFor(550, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 2)
  {
    BLift.spinFor(-550, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 3)
  {
    BLift.spinFor(500, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 4)
  {
    BLift.spinFor(-500, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }
  else
  {
    BLift.spinFor(liftDegrees, vex::rotationUnits (deg), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }
}

void autoBackLiftRevs (float liftRevolutions, int liftVelocity, bool doWaitForFinished, bool doHold, int toTopOrBottom = 0)
{
  liftRevolutions = liftRevolutions * 5;

  if (toTopOrBottom == 1)
  {
    BLift.spinFor(550, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 2)
  {
    BLift.spinFor(-550, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 3)
  {
    BLift.spinFor(500, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 4)
  {
    BLift.spinFor(-500, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else 
  {
    BLift.spinFor(liftRevolutions, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  if (doHold)
  {
    BLift.stop(hold);
  }
}

void autoBackLiftToRevAmount (float liftRevolutions, int liftVelocity, bool doWaitForFinished, bool doHold, int toTopOrBottom = 0)
{
  liftRevolutions = liftRevolutions * 5;

  if (toTopOrBottom == 1)
  {
    BLift.spinTo(0.5, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 2)
  {
    BLift.spinTo(-0.5, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 3)
  {
    BLift.spinFor(0.25, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (toTopOrBottom == 4)
  {
    BLift.spinFor(-0.25, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else 
  {
    BLift.spinFor(liftRevolutions, vex::rotationUnits (rev), liftVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  if (doHold)
  {
    BLift.stop(hold);
  }
}

void autonDriveUpRamp(int velocityPct, char sides, inertial& imu)
{
  
  imu.resetRotation();

  if (sides == 'b' || sides == 'B')
  {
    FL.spin(forward);
    BL.spin(forward);
    FR.spin(forward);
    BR.spin(forward);
    FR.setVelocity(velocityPct, percent);
    FL.setVelocity(velocityPct, percent);
    BR.setVelocity(velocityPct, percent);
    BL.setVelocity(velocityPct, percent);
  } 
    
  else if (sides == 'l' || sides == 'L')
  {
    FL.spin(forward);
    BL.spin(forward);
    FL.setVelocity(velocityPct, percent);
    BL.setVelocity(velocityPct, percent);
  } 
    
  else if (sides == 'r' || sides == 'R')
  {
    FR.spin(forward);
    BR.spin(forward);
    FR.setVelocity(velocityPct, percent);
    BR.setVelocity( velocityPct, percent);
  }

  while (fabs(imu.rotation(rotationUnits::deg)) < 10 && fabs(imu.pitch(rotationUnits::deg)))
  {
    Brain.Screen.print(imu.rotation(rotationUnits::deg));
    Brain.Screen.newLine();
  }

  FR.stop(brake);
  FL.stop(brake);
  BR.stop(brake);
  BL.stop(brake);
}

// void badAutoTurn (int turnDegrees, int velocityPct, int sides, bool doWaitForFinished)
// {
//   double wheelDeg = turnDegrees * 3.56;
//   if (sides == 0)
//   {
//     BL.spinFor(wheelDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//     FL.spinFor(wheelDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//     BR.spinFor(-1 * (wheelDeg), vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//     FR.spinFor(-1 * (wheelDeg), vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), doWaitForFinished);
//   } else if (sides == 1)
//   {
//     BL.spinFor(wheelDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//     FL.spinFor(wheelDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), doWaitForFinished);
//   }else if (sides == 2)
//   {
//     BR.spinFor(wheelDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//     FR.spinFor(wheelDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), doWaitForFinished);
//   }
// }

// void smoothTurn(float turnDegrees, int maxTurnSpeed, inertial& imu)
// {
//   timer clock = timer();
//   int turnSpeed = 10;

//   imu.resetRotation();

//   int turnDirection = 1;
//   if (turnDegrees < 0)
//   {
//     turnDirection = -1;
//   }
  
//   FR.setVelocity(turnDirection * turnSpeed * -1, percent);
//   FL.setVelocity(turnDirection * turnSpeed, percent);
//   BR.setVelocity(turnDirection * turnSpeed * -1, percent);
//   BL.setVelocity(turnDirection * turnSpeed, percent);

//   FR.spin(forward); 
//   FL.spin(forward); 
//   BR.spin(forward);
//   BL.spin(forward);

//   clock.reset();
//   // Increase speed for first half of the turn
//   while (fabs(imu.rotation(rotationUnits::deg)) < fabs(turnDegrees / 2))
//   {
//     // Increase speed every 100ms
//     if (clock.time(msec) > 100)
//     {
//       clock.reset();

//       turnSpeed += 10;
//       if (turnSpeed > maxTurnSpeed)
//       {
//         turnSpeed = maxTurnSpeed;
//       }

//       FR.setVelocity(turnDirection * turnSpeed * -1, percent);
//       FL.setVelocity(turnDirection * turnSpeed, percent);
//       BR.setVelocity(turnDirection * turnSpeed * -1, percent);
//       BL.setVelocity(turnDirection * turnSpeed, percent);
//     }
//   }
  
//   // Decrease speed for second half of the turn
//   clock.reset();
//   while(fabs(imu.rotation(rotationUnits::deg)) < fabs(turnDegrees))
//   {
//     if (clock.time(msec) > 100)
//     {
//       clock.reset();

//       turnSpeed -= 10;
//       if (turnSpeed < 10)
//       {
//         turnSpeed = 10;
//       }

//       FR.setVelocity(turnDirection * turnSpeed * -1, percent);
//       FL.setVelocity(turnDirection * turnSpeed, percent);
//       BR.setVelocity(turnDirection * turnSpeed * -1, percent);
//       BL.setVelocity(turnDirection * turnSpeed, percent);
//     }
//   } 
//   FR.stop(brake);
//   FL.stop(brake);
//   BR.stop(brake);
//   BL.stop(brake);
// }

/*void autonSpinnyThing (int turnDegrees, int turnVelocity, bool doWaitForFinished, int openOrClosed = 0)
{
  if (openOrClosed == 1)
  {
    spinnyThing.spinFor(325, vex::rotationUnits (deg), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else if (openOrClosed == 2)
  {
    spinnyThing.spinFor(-325, vex::rotationUnits (deg), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  else 
  {
    spinnyThing.spinFor(turnDegrees, vex::rotationUnits (deg), turnVelocity, vex::velocityUnits (pct), doWaitForFinished);
  }

  spinnyThing.stop(hold);
}*/

// void smootherTurn(float turnDegrees, int maxTurnSpeed, inertial& imu)
// {
//   int initialTurnSpeed = 10;

//   imu.resetRotation();

//   int turnDirection = 1;
//   if (turnDegrees < 0)
//   {
//     turnDirection = -1;
//   }

//   FR.setVelocity(0, percent);
//   FL.setVelocity(0, percent);
//   BR.setVelocity(0, percent);
//   BL.setVelocity(0, percent);

//   FR.spin(forward); 
//   FL.spin(forward); 
//   BR.spin(forward);
//   BL.spin(forward);

//   // Increase speed for first half of the turn
//   while (fabs(imu.rotation(rotationUnits::deg)) < fabs(turnDegrees / 2))
//   {
//     float fractionThroughFirstHalfTurn = fabs(imu.rotation(rotationUnits::deg)) / fabs(turnDegrees / 2);
//     float turnSpeed = initialTurnSpeed + (maxTurnSpeed - initialTurnSpeed) * fractionThroughFirstHalfTurn;

//     FR.setVelocity(turnDirection * turnSpeed * -1, percent);
//     FL.setVelocity(turnDirection * turnSpeed, percent);
//     BR.setVelocity(turnDirection * turnSpeed * -1, percent);
//     BL.setVelocity(turnDirection * turnSpeed, percent);
//   }
  
//   // Decrease speed for second half of the turn
//   while(fabs(imu.rotation(rotationUnits::deg)) < fabs(turnDegrees))
//   {
//     float fractionThroughSecondHalfTurn = (fabs(imu.rotation(rotationUnits::deg)) - fabs(turnDegrees / 2)) / fabs(turnDegrees / 2);
//     float turnSpeed = maxTurnSpeed - (maxTurnSpeed - initialTurnSpeed) * fractionThroughSecondHalfTurn;

//     FR.setVelocity(turnDirection * turnSpeed * -1, percent);
//     FL.setVelocity(turnDirection * turnSpeed, percent);
//     BR.setVelocity(turnDirection * turnSpeed * -1, percent);
//     BL.setVelocity(turnDirection * turnSpeed, percent);
//   } 

//   FR.stop(brake);
//   FL.stop(brake);
//   BR.stop(brake);
//   BL.stop(brake);
// }

// void smoothererTurn(inertial& imu)
// {
//   motor_group driveTrainLeft = motor_group(FL, BL);
//   motor_group driveTrainRight = motor_group(FR, BR);
//   smartdrive driveTrain = smartdrive(driveTrainLeft, driveTrainRight, imu, 12.566370614359172953850573533118, 1, 1, distanceUnits::in, 1.0);
//   driveTrain.turnToRotation(90, deg, 50, velocityUnits::pct, true);
// }

// void Drive (float inches, int velocityPct, bool doWaitForFinished, int unitType = 0)
// {
//   //float driveDeg = (inches / inchesPerDegree) * driveGearRatio;
//   float driveDeg = 0;
//   if (unitType == 0)
//   {
//     driveDeg = inches * 29.16666666666667;
//   }

//   if (unitType == 1)
//   {
//     driveDeg = inches * 39.3701;
//   }

//   else if (unitType == 2)
//   {
//     driveDeg = inches * 12;
//   }

//   else if (unitType == 3)
//   {
//     driveDeg = inches * 700;
//   }

//   FR.spinFor(driveDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//   BR.spinFor(driveDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//   FL.spinFor(driveDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), false);
//   BL.spinFor(driveDeg, vex::rotationUnits (deg), velocityPct, vex::velocityUnits (pct), doWaitForFinished);
// }