#define leftButton					1
#define centerButton				2
#define rightButton					4

typedef struct {
	char* topLine;
	char* botLine;

	int count;
	int maxCount;

	char* type;
	char* color;
	char* tile;
	int preloads;

	char* startTile;
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

void clearScreenLCD ()
{ //Clear LCD Display
	clearLCDLine(0);
	clearLCDLine(1);
}

void initializeScreenLCD ()
{ //Clear LCD display
	clearScreenLCD();
	//Turn on LCD backlight
	bLCDBacklight = true;
	//Clear LCD Timer
	clearTimer(T2);
}

void initializeLCD (int maxCount)
{
	clearScreenLCD();

	LCD.maxCount = maxCount;
}

void displayScreenLCD (char* topText, char* botText)
{
	LCD.topLine = topText;
	LCD.botLine = botText;
}

void selectOption (char* title, int optionCount)
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
	initializeLCD(4);

	while(nLCDButtons != centerButton)
	{	//While center button is not pressed
		selectOption("None", 0);

		selectOption("Tile", 1);

		selectOption("Field", 2);

		selectOption("Hoard", 3);

		selectOption("Skills", 4);
	}

	LCD.type = LCD.topLine;

	clearScreenLCD();
}

void selectStart ()
{
	waitRelease();

	if(LCD.type != "None" || LCD.type != "Program Skills")
	{
		while (nLCDButtons != leftButton && nLCDButtons != rightButton)
		{	//Select alliance color
			displayScreenLCD("Blue        Red", "<             >");

			if (nLCDButtons == leftButton)
			{
				waitRelease();
				LCD.color = "Blue";
			}

			else if (nLCDButtons == rightButton)
			{
				waitRelease();
				LCD.color = "Red";
			}
		}
		waitRelease();

		clearScreenLCD();

		while (nLCDButtons != leftButton && nLCDButtons != rightButton)
		{	//Select tile side
			displayScreenLCD("Inner     Outer", "<             >");

			if (nLCDButtons == leftButton)
			{
				waitRelease();
				LCD.tile = "Inner";
			}

			else if (nLCDButtons == rightButton)
			{
				waitRelease();
				LCD.tile = "Outer";
			}
		}

		waitRelease();

		initializeLCD(4);

		if (LCD.type != "Hoard")
		{
			while (nLCDButtons != centerButton)
			{	//Select number of preloads
				selectOption("0 (zero)", 0);
				selectOption("1 (one)", 1);
				selectOption("2 (two)", 2);
				selectOption("3 (three)", 3);
				selectOption("4 (four)", 4);
			}

			waitRelease();
		}
	}
	sprintf(LCD.startTile, LCD.color , " " , LCD.tile);
	clearScreenLCD();
}

void displayAutonomous ()
{
	string topText = "";
	string botText = "";

	sprintf(topText, LCD.type);
	sprintf(botText, LCD.color, " ", LCD.tile);
}

void displayBattery ()
{	//Function to display primary and backup battery level
	string primaryBattery;
	string secondaryBattery;
	string topText = "";
	string botText = "";

	//Initialize LCD Screen
	initializeScreenLCD();
	//Display primary battery level
	sprintf(primaryBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0, 'V');
	sprintf(topText, "Primary: ", primaryBattery);
	strcat(topText, primaryBattery);
	LCD.topLine = topText;
	//Display backup battery level
	sprintf(secondaryBattery, "%1.2f%c", powerExpanderVolts, 'V');
	sprintf(botText, "Secondary: ", secondaryBattery);
	LCD.botLine = botText;
}

task updateScreenLCD ()
{
	while(true)
	{
		displayLCDCenteredString(0, LCD.topLine);
		displayLCDCenteredString(1, LCD.botLine);
	}
}
