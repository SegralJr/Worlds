void runRollerIntake (int power)
{
	motor[roller] = power;
}

void runConveyorIntake (int power)
{
	motor[conveyor] = power;
}

void runIntake (int rollerPower, int conveyorPower)
{
	runRollerIntake(rollerPower);
	runConveyorIntake(conveyorPower);
}

int checkBallLoaded ()
{
	if (ballLoaded == 1 && flywheel.currentVelocity < (flywheel.targetVelocity - toleranceRPM))
		return 0;
	else
		return 1;
}

void intakeRC (int rollerControl1, int rollerControl2, int intakeControl1, int intakeControl2)
{
	int rollerControl = rollerControl1 - rollerControl2;
	int intakeControl = intakeControl1 - intakeControl2;
	int rollerPower;
	int conveyorPower;
	int ballLoaded;

	ballLoaded = checkBallLoaded();

	rollerPower = ((rollerControl + intakeControl) * 127) * ballLoaded;
	conveyorPower = (intakeControl * 127) * ballLoaded;

	runIntake(rollerPower, conveyorPower);
}
