typedef struct
{
	char* color;
	char* tile;

	int preloads;
} auton;

static auton auto;

void autonInit (auton *controller, char* color, char* tile)
{
	controller->color = color;
	controller->tile = tile;
}
