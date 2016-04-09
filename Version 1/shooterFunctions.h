void runFlywheel (int power)
{
	motor[flywheel1] = power;
	motor[flywheel2] = power;
	motor[flywheel3] = power;
	motor[flywheel4] = power;
}

task updateFlywheel
{
	int difference;
	int lastValue;
	while (true)
	{
		difference = flywheelEncoder - lastValue;
		lastValue = flywheelEncoder;
		wait1Msec(5);
		currentRPM = ((difference*100)/3);
	}
}

void setFlywheelRPM (int closeToggle, int midToggle, int farToggle, int stopToggle)
{
	if (stopToggle == 1)
		targetRPM = stopRPM;
	else if (closeToggle == 1)
		targetRPM = closeRPM;
	else if (midToggle == 1)
		targetRPM = midRPM;
	else if (farToggle == 1)
		targetRPM = farRPM;
}

void runFlywheelRPM (int goalRPM)
{
	pidController flywheel;
	pidInit(&flywheel, flyP, flyI, flyD, flyMaxPower, targetRPM);
	flywheel.currentVal = currentRPM;

	flywheelPower = pidCalculate(&flywheel);
	currentError = flywheel.error;

	runFlywheel(flywheelPower);
}

void flywheelRC ()
{
	setFlywheelRPM(closeShooterButton, midShooterButton, farShooterButton, stopShooterButton);
	runFlywheelRPM(targetRPM);
}
