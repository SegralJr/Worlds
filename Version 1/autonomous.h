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

void longRangeAuton ()
{
	flywheelAuton(&flywheel, farRPM, farDrive, farGain, 4);
}

void shortRangeAuton ()
{

}

void hoardingAuton ()
{

}

void execAuton ()
{

}
