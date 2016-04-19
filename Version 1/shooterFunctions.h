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

	int ballsInitial = ballsFired;

	while (true)
	{
		tbhUpdate(controller, flywheelEncoder);

		tbhCalculate(controller);

		controller->motorPower = (controller->drive * flyMaxPower) + 0.5;

		if (controller->targetVelocity == 0)
		{
			while (controller->motorPower > 0)
				controller->motorPower -= 1;
		}

		runFlywheel(controller->motorPower);

		debug_rpm = controller->currentVelocity;

		writeDebugStreamLine("%d %d %d", nPgmTime, controller->error, controller->integral);

		wait1Msec(flyLoopTime);
	}
}

void setFlywheelRPM (tbhController *controller, int closeToggle, int midToggle, int farToggle, int stopToggle)
{
	if (stopToggle == 1)
	{
		prepBalls();
		tbhInit (controller, stopRPM, stopDrive, closeKp, closeKi);
	}
	else if (closeToggle == 1)
	{
		prepBalls();
		tbhInit (controller, closeRPM, closeDrive, closeKp, closeKi);
	}
	else if (midToggle == 1)
	{
		prepBalls();
		tbhInit (controller, midRPM, midDrive, midKp, midKi);
	}
	else if (farToggle == 1)
	{
		prepBalls();
		tbhInit (controller, farRPM, farDrive, farKp, farKi);
	}
}

void tuneFlywheelRPM (tbhController *controller, int increment, int decrement)
{
	if (increment == 1)
	{
		controller->currentVelocity += scaleRPM;
		if (increment == 1) {wait1Msec(1);}
	}
	else if (decrement == 1)
	{
		controller->currentVelocity -= scaleRPM;
		if (decrement == 1) {wait1Msec(1);}
	}
}

void flywheelRC (tbhController *controller)
{
	setFlywheelRPM(controller, closeShooterButton, midShooterButton, farShooterButton, stopShooterButton);
	tuneFlywheelRPM(controller, incrementShooterButton, decrementShooterButton);
}

task trackBallsFired ()
{
	int ballWasFired = checkBallFiring();
	int ballIsFiring;

	while(true)
	{
		ballIsFiring = checkBallFiring();

		if (ballWasFired > ballIsFiring)
		{
			ballsFired += 1;
		}

		ballWasFired = ballIsFiring;

		wait1Msec (15);
	}
}

void flywheelAuton (tbhController *controller, int goalRPM, int predictedDrive, int Kp, int Ki, int balls)
{
	int ballsFiredInitial = ballsFired;

	prepBalls();

	tbhInit (controller, goalRPM, predictedDrive, Kp, Ki);

	while (controller->currentVelocity < controller->targetVelocity) {wait1Msec(1);}

	while (ballsFired < (balls + ballsFiredInitial))
	{
		runIntake(127, 127);
	}

	tbhInit (controller, stopRPM, stopDrive, closeKp, closeKi);
}
