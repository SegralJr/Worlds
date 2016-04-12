typedef struct
{
	char* color;
	char* tile;

	int preloads;
} auton;

static auton auto;

void selectColor (auton *controller, char* color)
{
	auto.color = color;
}
