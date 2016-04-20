typedef struct
{
	long currentTheta;
	long lastTheta;
	long lastTime;

	int currentVelocity;
	int targetVelocity;

	int error;
	int lastError;
	int integral;
	int derivative;

	float Kp;
	float Ki;
	int iLowerLimit;
	int iUpperLimit;

	float approxDrive;
	float drive;
	float driveAtZero;
	bool firstZero;

	int ballsInitial;

	int motorPower;
} tbhController;

static tbhController flywheel;

void tbhInit (tbhController *controller, int targetRPM, int predictedDrive, float Kp, float Ki)
{
	controller->targetVelocity = targetRPM;
	controller->approxDrive = predictedDrive;
	controller->Kp = Kp;
	controller->Ki = Ki;
	controller->iLowerLimit = iLowerLimit;
	controller->iUpperLimit = iUpperLimit;
	controller->ballsInitial = ballsFired;

	controller->error = controller->targetVelocity - controller->currentVelocity;

	controller->lastError = controller->error;
	controller->firstZero = true;
	controller->driveAtZero = 0;
}

void tbhUpdate (tbhController *controller, int encoderValue)
{
	int deltaTime;
	float deltaTheta;

	controller->currentTheta = encoderValue;
	deltaTheta = controller->currentTheta - controller->lastTheta;
	deltaTime = nSysTime - controller->lastTime;
	controller->lastTime = nSysTime;

	controller->lastTheta = controller->currentTheta;

	if (deltaTime < 1)
		controller->currentVelocity = 0;
	else
		controller->currentVelocity = ((deltaTheta * 500) / (deltaTime * 3));

	//controller->currentVelocity = controller->currentVelocity

}

void tbhCalculate (tbhController *controller)
{
	controller->error = controller->targetVelocity - controller->currentVelocity;

	if (controller->error > controller->iLowerLimit || controller->error < controller->iUpperLimit)
		controller->integral += controller->error;
	else
		controller->integral = 0;

	//controller->derivative = controller->error - controller->lastError;


	controller->drive = controller->drive + (controller->error * controller->Kp) + (controller->integral * controller->Ki);

	if (controller->drive > 1)
		controller->drive = 1;
	if (controller->drive < 0)
		controller->drive = 0;

	if (sgn(controller->error) != sgn(controller->lastError))
	{
		if (controller->firstZero)
		{
			controller->drive = controller->approxDrive;
			controller->firstZero = false;
		}
		else
		{
			//controller->drive = (0.5 * controller->drive + 0.5 * controller->driveAtZero);
			if (intakeRunning && controller->targetVelocity == closeRPM  )
			controller->drive = (0.1 * controller->drive + 0.9 * controller->driveAtZero);
			else
			controller->drive = (0.5 * controller->drive + 0.5 * controller->driveAtZero);
		}
		controller->driveAtZero = controller->drive;
	}
	controller->lastError = controller->error;
}
