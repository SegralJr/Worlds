void runDrive (int lPower, int rPower)
{
	motor[leftDrive1] = lPower;
	motor[leftDrive2] = lPower;
	motor[rightDrive1] = rPower;
	motor[rightDrive2] = rPower;
}

void driveRC (int lControl, int rControl)
{
	runDrive(lControl, rControl);
}

void driveAuton (int lGoalDistance, int rGoalDistance = lGoalDistance)
{
	int lPower;
	int rPower;
	int lGoalTicks = ((lGoalDistance * 392) / (4 * PI));
	int rGoalTicks = ((rGoalDistance * 392) / (4 * PI));

	pidController lDrive;
	pidInit(&lDrive, driveKp, driveKi, driveKd, lGoalTicks);
	lDrive.currentVal = lDriveEncoder;

	pidController rDrive;
	pidInit(&rDrive, driveKp, driveKi, driveKd, rGoalTicks);
	rDrive.currentVal = rDriveEncoder;

	while (abs(lDrive.currentVal) < abs(lGoalTicks) && abs(rDrive.currentVal) < abs(lGoalTicks))
	{
		lDrive.currentVal = lDriveEncoder;
		rDrive.currentVal = rDriveEncoder;

		lPower = pidCalculate(&lDrive);
		rPower = pidCalculate(&rDrive);

		runDrive(lPower, rPower);
	}

	runDrive(0, 0);
}

void turnAuton (int goalTicks)
{
	int power;

	pidController turn;
	pidInit(&turn, turnKp, turnKi, turnKd, goalTicks);
	turn.currentVal = gyroscopeValue;

	while (abs(turn.currentVal) < abs(goalTicks))
	{
		turn.currentVal = gyroscopeValue;
		power = pidCalculate(&turn);

		runDrive(power, -power);
	}
}
