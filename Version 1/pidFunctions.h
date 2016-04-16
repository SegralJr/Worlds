/*
This file contains all code pertaining to the PID
controller's "infrastructure" to allow for simple,
repeatable use of PID for any subsystem.
*/

typedef struct
{	//Struct to hold all variables necessary for the PID controller
	short enabled;

	//Constant Variables
	float kP;
	float kI;
	float kD;

	float kILimit;

	//Working Variables
	float error;
	float lastError;
	float integral;
	float derivative;

	//Input Variables
	long currentVal;
	long goalVal;
	long maxPower;

	//Output Variables
	int rawPower;
	int motorPower;
} pidController;

void pidInit (pidController *controller, float kP, float kI, float kD, long goalVal, long maxPower)
{	//Function to initialize PID controller
	//Set constant variables
	controller->kP = kP;
	controller->kI = kI;
	controller->kD = kD;
	controller->kILimit = 50;
	controller->maxPower = maxPower;
	//Reset working variables
	controller->error = controller->lastError = 0;
	controller->integral = controller->derivative = 0;
	//Set input variables
	controller->goalVal = goalVal;
}

int pidCalculate (pidController *controller)
{	//Function to calculate and return motor power
	//Calculate Error (P)
	controller->error = controller->goalVal - controller->currentVal;
	//Calculate Integral (I)
	controller->integral += controller->error;
	//Calculate Derivative (D)
	controller->derivative = controller->error - controller->lastError;
	//Reassign last error value
	controller->lastError = controller->error;

	//Check integral against top limit
	if(controller->integral > controller->kILimit)
		controller->integral = controller->kILimit;
	//Check integral against bottom limit
	else if(controller->integral < -controller->kILimit)
		controller->integral = -controller->kILimit;

	//Calculate raw motor power from P, I, and D
	controller->rawPower = ((controller->error * controller->kP)
												 +(controller->integral * controller->kI)
												 +(controller->derivative * controller->kD));

	//Refine raw motor power (127 to -127)
	if (abs(controller->rawPower) > controller->maxPower)
		controller->motorPower = sgn(controller->rawPower) * controller->maxPower;
	else
		controller->motorPower = controller->rawPower;

	//Return refined motor power
	return(controller->motorPower);
}
