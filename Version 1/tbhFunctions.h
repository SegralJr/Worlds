typedef struct
{
	long currentTheta;
	long lastTheta;
	long lastTime;

	int currentVelocity;
	int targetVelocity;

	int error;
	int lastError;

	float errorScale;
	float approxDrive;
	float drive;
	float driveAtZero;
	bool firstZero;

	int motorPower;
} tbhController;

static tbhController flywheel;

void tbhInit (tbhController *controller, int targetRPM, int predictedDrive, int gain)
{
	controller->targetVelocity = targetRPM;
	controller->approxDrive = predictedDrive;
	controller->errorScale = gain;

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
}

void tbhCalculate (tbhController *controller)
{
	controller->error = controller->targetVelocity - controller->currentVelocity;

	controller->drive = controller->drive + (controller->error * controller->errorScale);

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
			controller->drive = 0.5 * (controller->drive + controller->driveAtZero);

		controller->driveAtZero = controller->drive;
	}

	controller->lastError = controller->error;
}
