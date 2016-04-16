void runDrive (int lPower, int rPower)
{
	motor[leftDrive1] = lPower;
	motor[leftDrive2] = lPower;
	motor[rightDrive1] = rPower;
	motor[rightDrive2] = rPower;
}

void stopDriveMotors ()
{
	runDrive(0, 0);
}

void driveRC (int lControl, int rControl)
{
	runDrive(lControl, rControl);
}

void driveAuton (int lGoalDistance, int rGoalDistance = lGoalDistance, int maxPower = 127)
{
	int lPower;
	int rPower;
	int lGoalTicks = ((lGoalDistance * 392) / (4 * PI));
	int rGoalTicks = ((rGoalDistance * 392) / (4 * PI));

	pidController lDrive;
	pidInit(&lDrive, driveKp, driveKi, driveKd, lGoalTicks, maxPower);
	lDrive.currentVal = lDriveEncoder;

	pidController rDrive;
	pidInit(&rDrive, driveKp, driveKi, driveKd, rGoalTicks, maxPower);
	rDrive.currentVal = rDriveEncoder;

	while (abs(lDrive.currentVal) < abs(lGoalTicks) && abs(rDrive.currentVal) < abs(lGoalTicks))
	{
		lDrive.currentVal = lDriveEncoder;
		rDrive.currentVal = rDriveEncoder;

		lPower = pidCalculate(&lDrive);
		rPower = pidCalculate(&rDrive);

		runDrive(lPower, rPower);
	}

	stopDriveMotors();
	lDriveEncoder = 0;
	rDriveEncoder = 0;
}

void turnAuton (int goalTicks, int maxPower = 127)
{
	int power;

	pidController turn;
	pidInit(&turn, turnKp, turnKi, turnKd, goalTicks, maxPower);
	turn.currentVal = gyroscopeValue;

	while (abs(turn.currentVal) < abs(goalTicks))
	{
		turn.currentVal = gyroscopeValue;
		power = pidCalculate(&turn);

		runDrive(power, -power);
	}

	stopDriveMotors();
	SensorValue[gyroscope] = 0;
}
