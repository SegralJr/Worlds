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

void driveAuton (int lGoalTicks, int rGoalTicks = lGoalTicks)
{
	int lPower;
	int rPower;

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

void
