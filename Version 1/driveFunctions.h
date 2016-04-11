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
