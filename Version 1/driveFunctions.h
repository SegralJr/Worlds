void runDrive (int lPower, int rPower)
{
	motor[leftDrive] = lPower;
	motor[rightDrive] = rPower;
}

void driveRC (int lControl, int rControl)
{
	runDrive(lControl, rControl);
}
