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
	if (conveyorPower == 127)
		intakeRunning = true;
	else
		intakeRunning = false;
}

void stopIntakeMotors ()
{
	runIntake(0, 0);
}

int checkBallFiring ()
{
	if (ballLoaded && flywheel.targetVelocity > 0)
		return 1;
	else
		return 0;
}

void prepBalls ()
{
	while (ballLoaded == 1)
	{
		runIntake(0, -127);
	}
}

void intakeRC (int conveyorControl1, int conveyorControl2, int intakeControl1, int intakeControl2)
{
	int conveyorControl = conveyorControl1 - conveyorControl2;
	int intakeControl = intakeControl1 - intakeControl2;
	int rollerPower;
	int conveyorPower;

	rollerPower = (intakeControl * 127);
	conveyorPower = ((conveyorControl + intakeControl) * 127);

	runIntake(rollerPower, conveyorPower);
}

void intakeAutonTime (int rollerPower, int conveyorPower, int time)
{
	runIntake (rollerPower, conveyorPower);
	wait1Msec(time);
	stopIntakeMotors();
}

task intake ()
{
	while (true)
	{
		runIntake(127, 127);
	}
}
