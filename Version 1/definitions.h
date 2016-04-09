//Shooter Variables
int RPM_debug;
int power_debug;
int error_debug;
int target_debug;
int select_debug;

//Shooter Constants
int stopRPM = 0;
int closeRPM = 800;
int midRPM = 1800;
int farRPM = 2200;

float kFly = 0.01;
int flyMaxPower = 127;
int flyLoopTime = 10;

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
