//Sensor Redefinitions
#define flywheelEncoder 		(-SensorValue[flyEncoder])
#define lDriveEncoder 			SensorValue[leftDriveEncoder]
#define rDriveEncoder				SensorValue[rightDriveEncoder]
#define accelX 							SensorValue[accelerometerX]
#define accelY 							SensorValue[accelerometerY]
#define gyroscopeValue 			(-SensorValue[gyroscope])
#define ballLoaded					SensorValue[loadSwitch]

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
int closeRPM = 2000;
int midRPM = 2500;
int farRPM = 3000;
int skillsRPM = 2900;
int toleranceRPM = 200;
int scaleRPM = 50;

float closeGain = 0.00003;
float midGain = 0.00006;
float farGain = 0.00008;

float stopDrive = 0;
float closeDrive = 0.4;
float midDrive = 0.6;
float farDrive = 0.8;

int flyMaxPower = 100;
int flyLoopTime = 5;
