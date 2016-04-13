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

int checkBallLoaded (int sensor)
{

}

void intakeRC (int rollerControl1, int rollerControl2,
							 int intakeControl1, int intakeControl2)
{
	int rollerControl = rollerControl1 - rollerControl2;
	int intakeControl = intakeControl1 - intakeControl2;
	int rollerPower;
	int conveyorPower;

	if (

	rollerPower = (rollerControl + intakeControl) * 127;
	conveyorPower = intakeControl * 127;

	runIntake(rollerPower, conveyorPower);
}
