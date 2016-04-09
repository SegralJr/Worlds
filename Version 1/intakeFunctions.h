void runRollerIntake (int power)
{
	motor[roller] = power;
}

void runConveyorIntake (int power)
{
	motor[conveyor] = power;
}

void intakeRC (int rollerControl1, int rollerControl2,
							 int intakeControl1, int intakeControl2)
{
	int rollerControl = rollerControl1 - rollerControl2;
	int intakeControl = intakeControl1 - intakeControl2;
	int rollerPower;
	int conveyorPower;

	rollerPower = (rollerControl + intakeControl) * 127;
	conveyorPower = intakeControl * 127;

	runRollerIntake(rollerPower);
	runConveyorIntake(conveyorPower);
}
