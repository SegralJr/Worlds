int ballsFired;

//Sensor Redefinitions
#define flywheelEncoder 		(-SensorValue[flyEncoder])
#define lDriveEncoder 			SensorValue[leftDriveIME]
#define rDriveEncoder				SensorValue[rightDriveIME]
#define accelX 							SensorValue[accelerometerX]
#define accelY 							SensorValue[accelerometerY]
#define gyroscopeValue 			(-SensorValue[gyroscope])
#define ballLoaded					SensorValue[loadSwitch]
#define powerExpanderVolts	(SensorValue[powerExpander] / 280)

//Controller Redefinitions
#define lDriveControl						vexRT[Ch3]
#define rDriveControl 					vexRT[Ch2]
#define inRollerButton	 				vexRT[Btn5U]
#define outRollerButton					vexRT[Btn5D]
#define upIntakeButton 					vexRT[Btn6U]
#define downIntakeButton	 			vexRT[Btn6D]
#define stopShooterButton				vexRT[Btn7D]
#define closeShooterButton 			vexRT[Btn7L]
#define midShooterButton 				vexRT[Btn7U]
#define farShooterButton				vexRT[Btn7R]
#define incrementShooterButton	vexRT[Btn8R]
#define decrementShooterButton	vexRT[Btn8D]

//Shooter Constants
int stopRPM = 0;
int closeRPM = 130;
int midRPM = 170;
int farRPM = 210;
int skillsRPM = 150;
int toleranceRPM = 10;
int scaleRPM = 5;

float closeGain = 0.0003;
float midGain = 0.00035;
float farGain = 0.0004;

float stopDrive = 0;
float closeDrive = 0.4;
float midDrive = 0.6;
float farDrive = 0.8;

int flyMaxPower = 100;
int flyLoopTime = 5;

//Drive Constants
float driveKp = 0.8;
float driveKi = 0;
float driveKd = 0;

float turnKp = 0.8;
float turnKi = 0;
float turnKd = 0;
