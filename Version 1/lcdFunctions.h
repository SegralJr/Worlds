/*
This file is used to contain all functions
and task related to the LCD display, including
its use in autonomous selection and battery display
*/

void waitPress ()
{	//Wait for button to be pressed
	while (nLCDButtons == 0) { }
	wait1Msec(5);
}

void waitRelease ()
{ //Wait for button to be released
	while (nLCDButtons != 0) { }
	wait1Msec(5);
}

void initializeLCD ()
{ //Clear LCD display
	clearLCDLine(0);
	clearLCDLine(1);
	//Turn on LCD backlight
	bLCDBacklight = true;
	//Clear LCD Timer
	clearTimer(T2);
}

void clearScreenLCD ()
{ //Clear LCD Display
	clearLCDLine(0);
	clearLCDLine(1);
}

void displayScreenLCD (char* topLine, char* botLine)
{
	displayLCDCenteredString(0, topLine);
	displayLCDCenteredString(1, botLine);
}

void autonOption (char* title, int optionCount)
{
	if (count == optionCount)
	{
		//Display blue outer autonomous
		displayScreenLCD(title, "<     Enter    >");
		waitPress();

		//Decrement count if left button is pressed
		if(nLCDButtons == leftButton)
		{
			waitRelease();
			if (optionCount == 0)
				count = maxCount;
			else
				count += -1;
		}
		//Increment count if right button is pressed
		else if (nLCDButtons == rightButton)
		{
			waitRelease();
			if (optionCount == maxCount)
				count = 0;
			else
				count += 1;
		}
	}
}
void selectAuton ()
{ //Function to use LCD screen to select autonomous
	//Initialize LCD Screen
	initializeLCD();

	while(nLCDButtons != centerButton || lcdTimer < 25)
	{	//While center button is not pressed
		autonOption("No Autonomous", 0);

		autonOption("Long Range", 1);

		autonOption("Mid Range", 2);

		autonOption("Defense", 3);

		autonOption("Program Skills", 4);
	}

	clearScreenLCD();
	displayScreenLCDCentered("7701Z", "Ready");
}

void selectTile ()
{
	waitRelease();

	if (count == 2)
	{
		clearScreenLCD();

		while (nLCDButtons != leftButton && nLCDButtons != rightButton)
		{
			displayScreenLCD("Left      Right", "<             >");

			if (nLCDButtons == leftButton)
			{
				waitRelease();
				tileCount = 0;
			}

			else if (nLCDButtons == rightButton)
			{
				waitRelease();
				tileCount = 1;
			}
		}
		clearScreenLCD();
		displayScreenLCD("7701Z", "Ready");
	}
}

void execAuton ()
{ //Function to run autonomous based upon lcd selection
	//Initialize LCD Screen
	initializeLCD();

	if (count == 0)
	{	//No Autonomous
		//Display autonomous selection
		displayScreenLCD("No Autonomous", "Is Running");
		//Execute no autonomous
	}	//End case

	else if (count == 1)
	{	//Match Autonomous
		//Display autonomous selection
		displayScreenLCD("Running", "Long Range");
		//Execute match autonomous routine
		longRangeAuton();
	}	//End case

	else if (count == 2)
	{	//Match Autonomous
		//Display autonomous selection
		displayScreenLCD("Running", "Mid Range");
		//Execute match autonomous routine
		midRangeAuton();
	}	//End case

	else if (count == 3)
	{	//Defense Autonomous
		//Display autonomous selection
		displayScreenLCD("Running", "Hoard");
		//Execute programming skills routine
		DefenseAuton();
	}	//End case

	else if (count == 4)
	{	//Programming Skills
		//Display autonomous selection
		displayScreenLCD("Running", "Prog Skills");
		//Execute programming skills routine
		programmingSkills();
	}	//End case
}

void displayBattery ()
{	//Function to display primary and backup battery level
	//Initialize LCD Screen
	initializeLCD();
	//Display primary battery level
	displayLCDString(0, 0, "Primary: ");
	sprintf(primaryBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'V');
	displayNextLCDString(primaryBattery);
	//Display backup battery level
	displayLCDString(1, 0, "Fired:  ");
	sprintf(numberBallsFired, "1.2%f", ballsFired);
	displayNextLCDString(numberBallsFired);
}
