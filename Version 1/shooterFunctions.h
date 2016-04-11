void runFlywheel (int power)
{
	motor[flywheel1] = power;
	motor[flywheel2] = power;
	motor[flywheel3] = power;
	motor[flywheel4] = power;
}

task flywheelTBHControl
{
	tbhController *controller = &flywheel;

	while (true)
	{
		tbhUpdate(controller, flywheelEncoder);

		tbhCalculate(controller);

		controller->motorPower = (controller->drive * flyMaxPower) + 0.5;

		runFlywheel(controller->motorPower);

		wait1Msec(flyLoopTime);
	}
}

void setFlywheelRPM (tbhController *controller, int closeToggle, int midToggle, int farToggle, int stopToggle)
{
	if (stopToggle == 1)
		tbhInit (controller, stopRPM, 0);
	else if (closeToggle == 1)
		tbhInit (controller, closeRPM, 0.4);
	else if (midToggle == 1)
		tbhInit (controller, midRPM, 0.6);
	else if (farToggle == 1)
		tbhInit (controller, farRPM, 0.8);
}

void flywheelRC (tbhController *controller)
{
	setFlywheelRPM(controller, closeShooterButton, midShooterButton, farShooterButton, stopShooterButton);
}
