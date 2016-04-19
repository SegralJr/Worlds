void noAuton ()
{

}

void testAuton()
{
	startTask(intake);
	wait1Msec(100);
	runIntake(127, 127);
	driveAuton(3, 3, 30);
	driveAuton(-6, -6, 30);
	driveAuton(8);
	wait1Msec(300);
	stopTask(intake);
}

void programmingSkills ()
{
	flywheelAuton(&flywheel, skillsRPM, midDrive, midKp, midKi, 32);
	tbhInit(&flywheel, stopRPM, stopDrive, closeKp, closeKi);
	turnAuton(-900);
	driveAuton(120);
	turnAuton(900);
	flywheelAuton(&flywheel, skillsRPM, midDrive, midKp, midKi, 32);
	tbhInit(&flywheel, stopRPM, stopDrive, closeKp, closeKi);
}

void tileAuton ()
{
	flywheelAuton(&flywheel, farRPM, farDrive, farKp, farKi, LCD.preloads);
	tbhInit(&flywheel, stopRPM, stopDrive, closeKp, closeKi);
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
	tbhInit(&flywheel, 200, farDrive, farKp, farKi);
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
	flywheelAuton(&flywheel, midRPM, midDrive, midKp, midKi, 3);
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
