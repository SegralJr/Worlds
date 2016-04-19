#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    accelerometerX, sensorAccelerometer)
#pragma config(Sensor, in2,    accelerometerY, sensorAccelerometer)
#pragma config(Sensor, in3,    gyroscope,      sensorGyro)
#pragma config(Sensor, in4,    powerExpander,  sensorAnalog)
#pragma config(Sensor, in5,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl1,  loadSwitch,     sensorTouch)
#pragma config(Sensor, dgtl2,  flyEncoder,     sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  leftDriveIME,   sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Sensor, I2C_2,  rightDriveIME,  sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           roller,        tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           leftDrive1,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive2,   tmotorVex393HighSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port4,           flywheel1,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port5,           flywheel2,     tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           flywheel3,     tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           flywheel4,     tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftDrive2,    tmotorVex393HighSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port9,           rightDrive1,   tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          conveyor,      tmotorVex393TurboSpeed_HBridge, openLoop, reversed)
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
#include "intakeFunctions.h"
#include "shooterFunctions.h"
#include "driveFunctions.h"
#include "lcdFunctions.h"
#include "autonomous.h"

//Pre-Autonomous

void pre_auton()
{
	bStopTasksBetweenModes = false;
	startTask(updateScreenLCD);
	/*
	selectAuton();
	selectStart();
	*/
}

//Autonomous

task autonomous()
{
	/*
	startTask (flywheelTBHControl, 10);
	displayAutonomous();
	execAuton();
	*/
	testAuton();
}

//Driver Control

task usercontrol()
{
	startTask(trackBallsFired);
	startTask(flywheelTBHControl, 30);

	while (true)
	{
		driveRC(lDriveControl*0.875, rDriveControl);
		intakeRC(inRollerButton, outRollerButton, upIntakeButton, downIntakeButton);
		flywheelRC(&flywheel);

		displayBattery();
	}
}
