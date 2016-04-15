void programmingSkills ()
{
	flywheelAuton(&flywheel, skillsRPM, midDrive, midGain, 32);
	turnAuton(-900);
	driveAuton(120);
	turnAuton(900);
	flywheelAuton(&flywheel, skillsRPM, midDrive, midGain, 32);
}
