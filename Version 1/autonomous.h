typedef struct{
	char* color;
	char* tile;

	int preloads;

} auto;

static auto auton;

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

void
