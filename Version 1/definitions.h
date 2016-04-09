//Shooter Variables
int encoderValues[10];
float currentRPM;
int flywheelPower;
int currentError;
int targetRPM = 0;


//Shooter Constants
int stopRPM = 0;
int closeRPM = 800;
int midRPM = 1800;
int farRPM = 2200;

float flyP = 0.01;
float	flyI = 0;
float flyD = 0;
int flyMaxPower = 40;

//Sensor Redefinitions
#define flywheelEncoder 		(-SensorValue[flyEncoder])
#define lDriveEncoder 			SensorValue[leftDriveEncoder]
#define rDriveEncoder				SensorValue[rightDriveEncoder]
#define accelerometerValue 	SensorValue[accelerometer]
#define gyroscopeValue 			SensorValue[gyroscope]

//Controller Redefinitions
#define lDriveControl				vexRT[Ch3]
#define rDriveControl 			vexRT[Ch2]
#define inRollerButton	 		vexRT[Btn5U]
#define outRollerButton			vexRT[Btn5D]
#define upIntakeButton 			vexRT[Btn6U]
#define downIntakeButton	 	vexRT[Btn6D]
#define toggleShooterButton vexRT[Btn8D]
#define stopShooterButton		vexRT[Btn7D]
#define closeShooterButton 	vexRT[Btn7L]
#define midShooterButton 		vexRT[Btn7U]
#define farShooterButton		vexRT[Btn7R]
