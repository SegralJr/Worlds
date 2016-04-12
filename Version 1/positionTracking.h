typedef struct
{
	float xSensor;
	float ySensor;
	float angle;

	float xVelocity;
	float yVelocity;

	float xDisplacement;
	float yDisplacement;

	float xPosition;
	float yPosition;
} positionTracking;

void updateSensors (positionTracking *pos, int xAccelSensor, int yAccelSensor, int angleSensor)
{
	pos->xAccel = (xAccelSensor * gravity); //Translate to m/Ms
	pos->yAccel = (yAccelSensor * gravity); //Transalte to m/Ms
	pos->angle = (angleSensor / 10); //Translate to degrees
}

void calcAverage (positionTracking *pos)
{
	int currentXAccel;
	int currentYAccel;
	int currentAngle;

	translateAccel (xAccelSensor, currentXAccel);
	translateAccel (yAccelSensor, currentYAccel);
	totalAccel += currentAccel;
	totalAngle += currentAngle;
	avgCount += currentAngle;
	outputAccel = (totalAccel/avgCount);
	outputAngle = (totalAngle/avgCount);
}

void calcAccel (int currentXAccel, int currentYAccel, int currentAngle)
{
	xAccel = (currentXAccel * cosDegrees(currentAngle) + currentYAccel * sinDegrees(currentAngle));
	yAccel = (currentXAccel * sinDegrees(currentAngle) + currentYAccel * cosDegrees(currentAngle));
}

void calcVelocity (int currentAccelX, int currentAccelY)
{
	xVelocity = (currentAccelX * (waitTime/1000));
	yVelocity = (currentAccelY * (waitTime/1000));
}

void calcDisplacement (float currentAccelX, float currentAccelY)
{
	xDisplacement = ((currentAccelX * (waitTime/1000)^2) * 0.5);
	yDisplacement = ((currentAccelY * (waitTime/1000)^2) * 0.5);
}

void updateTracker ()
{
	xPosition += xDisplacement;
	yPosition += yDisplacement;
}

task calcTracker ()
{
	while (true)
	{
		float xAccelSensor = xAccelValue;
		float	yAccelSensor = yAccelValue;
		int angleSensor = gyroValue;

		while(time1[T1] < waitTime)
		{
			calcAverage(accelSensor, angleSensor, avgXAccel, avgAngle);
		}

		calcAccel(avgAccel, avgAngle);
		calcVelocity(xAccel, yAccel);
		calcDisplacement(xAccel, yAccel);
		updateTracker();
		clearTimer(T1);
	}
}
