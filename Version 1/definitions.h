int debug_rpm;
int debug_drive;

int ballsFired;
string team = "7701Z";

//Sensor Redefinitions
#define flywheelEncoder 		(-SensorValue[flyEncoder])
#define lDriveEncoder 			SensorValue[leftDriveIME]
#define rDriveEncoder				SensorValue[rightDriveIME]
#define accelX 							SensorValue[accelerometerX]
#define accelY 							SensorValue[accelerometerY]
#define gyroscopeValue 			(-SensorValue[gyroscope])
#define ballLoaded					SensorValue[loadSwitch]
#define powerExpanderVolts	(SensorValue[powerExpander] / 280)
#define lightValue					SensorValue[lightSensor]

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
int closeRPM = 140;
int midRPM = 160;
int farRPM = 210;
int skillsRPM = 150;
int toleranceRPM = 20;
int scaleRPM = 5;

float closeKp = 0.0012;
float midKp = 0.0005;
float farKp = 0.0005;

float closeKi = 0.0000002;
float midKi = 0.0002;
float farKi = 0.00045;

int iLowerLimit = 0;
int iUpperLimit = 35;

float stopDrive = 0;
float closeDrive = 0.4;
float midDrive = 0.6;
float farDrive = 0.8;

int flyMaxPower = 100;
int flyLoopTime = 25;

//Drive Constants
float driveKp = 0.8;
float driveKi = 0;
float driveKd = 0;

float turnKp = 0.8;
float turnKi = 0;
float turnKd = 0;

//Intake Variables
bool intakeRunning;
