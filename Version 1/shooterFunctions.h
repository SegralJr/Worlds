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

		writeDebugStreamLine("nPgmTime|controller->gain|controller->motorPower|controller->currentVelocity");

		wait1Msec(flyLoopTime);
	}
}

void setFlywheelRPM (tbhController *controller, int closeToggle, int midToggle, int farToggle, int stopToggle)
{
	if (stopToggle == 1)
		tbhInit (controller, stopRPM, stopDrive, closeGain);
	else if (closeToggle == 1)
		tbhInit (controller, closeRPM, closeDrive, closeGain);
	else if (midToggle == 1)
		tbhInit (controller, midRPM, midDrive, midGain);
	else if (farToggle == 1)
		tbhInit (controller, farRPM, farDrive, farGain);
}

void tuneFlywheelRPM (tbhController *controller, int increment, int decrement)
{
	if (increment == 1)
	{
		controller->currentVelocity += scaleRPM;
		while (increment == 1) {wait1Msec(1);}
	}
	else if (decrement == 1)
	{
		controller->currentVelocity -= scaleRPM;
		while (decrement == 1) {wait1Msec(1);}
	}
}

void flywheelRC (tbhController *controller)
{
	setFlywheelRPM(controller, closeShooterButton, midShooterButton, farShooterButton, stopShooterButton);
	tuneFlywheelRPM(controller, incrementShooterButton, decrementShooterButton);
}

void flywheelAuton (tbhController *controller, int goalRPM, int predictedDrive, int gain, int balls)
{
	tbhInit (controller, goalRPM, predictedDrive, gain);


}
