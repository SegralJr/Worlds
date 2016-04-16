void noAuton ()
{

}

void programmingSkills ()
{
	flywheelAuton(&flywheel, skillsRPM, midDrive, midGain, 32);
	tbhInit(&flywheel, stopRPM, stopDrive, closeGain);
	turnAuton(-900);
	driveAuton(120);
	turnAuton(900);
	flywheelAuton(&flywheel, skillsRPM, midDrive, midGain, 32);
	tbhInit(&flywheel, stopRPM, stopDrive, closeGain);
}

void tileAuton ()
{
	flywheelAuton(&flywheel, farRPM, farDrive, farGain, LCD.preloads);
	tbhInit(&flywheel, stopRPM, stopDrive, closeGain);
	if (LCD.startTile == "Red Inner" || LCD.startTile == "Blue Outer")
		turnAuton(200);
	else
		turnAuton(-200);
	runIntake(127, 127);
	driveAuton(30);
	driveAuton(-3);
	driveAuton(5);
	stopIntakeMotors();
	if (LCD.startTile == "Blue Outer" || LCD.startTile == "Red Inner")
		turnAuton(-450);
	else
		turnAuton(450);
	tbhInit(&flywheel, 200, farDrive, farGain);
	//***
	while(flywheel.currentVelocity > flywheel.targetVelocity - toleranceRPM)
		runIntake(127, 127);
	//***
}

void outerFieldAuton ()
{
	runIntake(127, 127);
	driveAuton(110);
	driveAuton(-3);
	driveAuton(5);
	stopIntakeMotors();
	if (LCD.color == "Blue")
		turnAuton(400);
	else
		turnAuton(-400);
	flywheelAuton(&flywheel, midRPM, midDrive, midGain, 3);
}

void innerFieldAuton ()
{

}

void fieldAuton ()
{
	if (LCD.tile == "Outer")
		outerFieldAuton();
	else
		innerFieldAuton();
}

void hoardAuton ()
{

}

void execAuton ()
{ //Function to run autonomous based upon lcd selection
	//Initialize LCD Screen
	initializeScreenLCD();

	if (LCD.type == "None")
	{	//No Autonomous
		//Execute no autonomous
		noAuton();
	}	//End case

	else if (LCD.type == "Tile")
	{	//Match Autonomous
		//Execute match autonomous routine
		tileAuton();
	}	//End case

	else if (LCD.type == "Far")
	{	//Match Autonomous
		//Execute match autonomous routine
		fieldAuton();
	}	//End case

	else if (LCD.type == "Hoard")
	{	//Defense Autonomous
		//Execute programming skills routine
		hoardAuton();
	}	//End case

	else if (LCD.type == "Skills")
	{	//Programming Skills
		//Execute programming skills routine
		programmingSkills();
	}	//End case
}
