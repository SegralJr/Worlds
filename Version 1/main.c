#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    accelerometerX, sensorAccelerometer)
#pragma config(Sensor, in2,    accelerometerY, sensorAccelerometer)
#pragma config(Sensor, in3,    gyroscope,      sensorGyro)
#pragma config(Sensor, in4,    powerExpander,  sensorAnalog)
#pragma config(Sensor, dgtl1,  loadSwitch,     sensorTouch)
#pragma config(Sensor, dgtl2,  flyEncoder,     sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  rightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_3,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           conveyor,      tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rightDrive1,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           rightDrive2,   tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           flywheel1,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           flywheel2,     tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port6,           flywheel3,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           flywheel4,     tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftDrive2,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port9,           leftDrive1,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          roller,        tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"
#include "definitions.h"
#include "tbhFunctions.h"
#include "pidFunctions.h"
#include "shooterFunctions.h"
#include "driveFunctions.h"
#include "intakeFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
  // .....................................................................................
  // Insert user code here.
  // .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
	startTask(flywheelTBHControl);

	while (true)
	{
		driveRC(lDriveControl, rDriveControl);
		intakeRC(inRollerButton, outRollerButton, upIntakeButton, downIntakeButton);
		flywheelRC(&flywheel);
	}
}
