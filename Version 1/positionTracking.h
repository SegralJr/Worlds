typedef struct
{
	float accelX;
	float accelY;
	int currentAngle;
} positionTracking;

void translateAccel (int accelSensor, int currentAccel)
{
	currentAngle = (angleSensor/10); //Translate to degrees
	currentAccel = accelSensor*gravity; //Translate to m/Ms
}

void translateGyro (int angleSensor, int currentAngle)
{
	currentAngle = (angleSensor/10)
}

void calcAverage (int xAccelSensor, int yAccelSensor, int angleSensor, int outputAccel, int outputAngle)
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
