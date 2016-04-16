#define leftButton					1
#define centerButton				2
#define rightButton					4

typedef struct {
	char* topLine;
	char* botLIne;

	int count;
	int maxCount;

	char* color;
	char* tile;

	int lcdTimeout;
} lcdScreen;

static lcdScreen LCD;

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

void displayScreenLCD (char* topText, char* botText)
{
	LCD.topLine = topText;
	LCD.botLine = botText;
}

void autonOption (char* title, int optionCount)
{
	if (LCD.count == optionCount)
	{
		//Display blue outer autonomous
		displayScreenLCD(title, "<     Enter    >");
		waitPress();

		//Decrement count if left button is pressed
		if(nLCDButtons == leftButton)
		{
			waitRelease();
			if (optionCount == 0)
				LCD.count = LCD.maxCount;
			else
				LCD.count -= 1;
		}
		//Increment count if right button is pressed
		else if (nLCDButtons == rightButton)
		{
			waitRelease();
			if (optionCount == LCD.maxCount)
				LCD.count = 0;
			else
				LCD.count += 1;
		}
	}
}

void selectAuton ()
{ //Function to use LCD screen to select autonomous
	//Initialize LCD Screen
	initializeLCD();

	while(nLCDButtons != centerButton)
	{	//While center button is not pressed
		autonOption("No Autonomous", 0);

		autonOption("Long Range", 1);

		autonOption("Mid Range", 2);

		autonOption("Defense", 3);

		autonOption("Program Skills", 4);
	}

	clearScreenLCD();
}

void selectTile ()
{
	waitRelease();
	while (nLCDButtons != leftButton && nLCDButtons != rightButton)
	{
		displayScreenLCD("Blue        Red", "<             >");

		if (nLCDButtons == leftButton)
		{
			waitRelease();
			LCD.color = "blue";
		}

		else if (nLCDButtons == rightButton)
		{
			waitRelease();
			LCD.color = "red";
		}
	}
	clearScreenLCD();

	waitRelease();
	while (nLCDButtons != leftButton && nLCDButtons != rightButton)
	{
		displayScreenLCD("Inner     Outer", "<             >");

		if (nLCDButtons == leftButton)
		{
			waitRelease();
			LCD.tile = "inner";
		}

		else if (nLCDButtons == rightButton)
		{
			waitRelease();
			LCD.tile = "outer";
		}
	}
	clearScreenLCD();
}

void execAuton ()
{ //Function to run autonomous based upon lcd selection
	//Initialize LCD Screen
	initializeLCD();

	if (LCD.count == 0)
	{	//No Autonomous
		//Display autonomous selection
		displayScreenLCD("No Autonomous", "Is Running");
		//Execute no autonomous
	}	//End case

	else if (LCD.count == 1)
	{	//Match Autonomous
		//Display autonomous selection
		displayScreenLCD("Running", "Long Range");
		//Execute match autonomous routine
		longRangeAuton();
	}	//End case

	else if (LCD.count == 2)
	{	//Match Autonomous
		//Display autonomous selection
		displayScreenLCD("Running", "Mid Range");
		//Execute match autonomous routine
		midRangeAuton();
	}	//End case

	else if (LCD.count == 3)
	{	//Defense Autonomous
		//Display autonomous selection
		displayScreenLCD("Running", "Hoard");
		//Execute programming skills routine
		DefenseAuton();
	}	//End case

	else if (LCD.count == 4)
	{	//Programming Skills
		//Display autonomous selection
		displayScreenLCD("Running", "Prog Skills");
		//Execute programming skills routine
		programmingSkills();
	}	//End case
}

//**
void displayBattery ()
{	//Function to display primary and backup battery level
	float primaryBattery;
	float secondaryBattery;
	//Initialize LCD Screen
	initializeLCD();
	//Display primary battery level
	displayLCDString(0, 0, "Primary: ");
	sprintf(primaryBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'V');
	displayScreenLCD("Primary: ", primaryBattery);
	//Display backup battery level
	displayLCDString(1, 0, "Fired:  ");
	sprintf(secondaryBattery, "%1.2%f%c", powerExpanderVolts, 'V');
	displayNextLCDString("Secondary: ", secondaryBattery);
}

task updateScreenLCD ()
{
	int deltaTime;
	while(true)
	{

	}
}
